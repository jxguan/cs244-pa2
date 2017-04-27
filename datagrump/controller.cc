#include <iostream>

#include "controller.hh"
#include "timestamp.hh"

using namespace std;

/* Default constructor */
Controller::Controller( const bool debug )
  : debug_( debug )
{}

/* Get current window size, in datagrams */
unsigned int Controller::window_size( void )
{
  /* Default: fixed window size of 100 outstanding datagrams */
  unsigned int the_window_size = rate;

  if ( debug_ ) {
    cerr << "At time " << timestamp_ms()
	 << " window size is " << the_window_size << endl;
  }

  return the_window_size;
}

/* A datagram was sent */
void Controller::datagram_was_sent( const uint64_t sequence_number,
				    /* of the sent datagram */
				    const uint64_t send_timestamp )
                                    /* in milliseconds */
{
  /* Default: take no action */

  if ( debug_ ) {
    cerr << "At time " << send_timestamp
	 << " sent datagram " << sequence_number << endl;
  }
}

/* An ack was received */
void Controller::ack_received( const uint64_t sequence_number_acked,
			       /* what sequence number was acknowledged */
			       const uint64_t send_timestamp_acked,
			       /* when the acknowledged datagram was sent (sender's clock) */
			       const uint64_t recv_timestamp_acked,
			       /* when the acknowledged datagram was received (receiver's clock)*/
			       const uint64_t timestamp_ack_received )
                               /* when the ack was received (by sender) */
{
  if ( debug_ ) {
    cerr << "At time " << timestamp_ack_received
	 << " received ack for datagram " << sequence_number_acked
	 << " (send @ time " << send_timestamp_acked
	 << ", received @ time " << recv_timestamp_acked << " by receiver's clock)"
	 << endl;
  }

  double new_rtt = timestamp_ack_received - send_timestamp_acked;

  double new_rtt_diff = new_rtt - prev_rtt;
  prev_rtt = new_rtt;
  rtt_diff = (1 - ALPHA) * rtt_diff + ALPHA * new_rtt_diff;

  double normalized_gradient = rtt_diff / MIN_RTT;

  if (new_rtt < T_LOW) {
    rate += DELTA;
    return;
  }
  if (new_rtt > T_HIGH) {
    rate *= (1 - BETA * (1- T_HIGH / new_rtt));
    if (rate < 1) {
      rate = 1;
    }
    return;
  }
  if (normalized_gradient <= 0) {
    rate += N * DELTA;
  } else {
    rate *= (1 - BETA * normalized_gradient);
  }
  if (rate < 1) {
    rate = 1;
  }
}

/* How long to wait (in milliseconds) if there are no acks
   before sending one more datagram */
unsigned int Controller::timeout_ms( void )
{
  return 1000; /* timeout of one second */
}
