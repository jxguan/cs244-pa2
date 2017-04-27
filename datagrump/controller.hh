#ifndef CONTROLLER_HH
#define CONTROLLER_HH

#include <cstdint>

/* Congestion controller interface */

class Controller
{
private:
  const double ALPHA = 0.25;
  const double BETA = 0.4;
  const double DELTA = 0.1;

  const unsigned int T_LOW = 80;
  const unsigned int T_HIGH = 150;
  const unsigned int MIN_RTT = 50;
  const double MIN_RATE = 1.0;
  const unsigned int N = 1;

  bool debug_; /* Enables debugging output */

  unsigned int prev_rtt = MIN_RTT;
  double rtt_diff = 0;
  double rate = 50;

  /* Add member variables here */

public:
  /* Public interface for the congestion controller */
  /* You can change these if you prefer, but will need to change
     the call site as well (in sender.cc) */

  /* Default constructor */
  Controller( const bool debug );

  /* Get current window size, in datagrams */
  unsigned int window_size( void );

  /* A datagram was sent */
  void datagram_was_sent( const uint64_t sequence_number,
			  const uint64_t send_timestamp );

  /* An ack was received */
  void ack_received( const uint64_t sequence_number_acked,
		     const uint64_t send_timestamp_acked,
		     const uint64_t recv_timestamp_acked,
		     const uint64_t timestamp_ack_received );

  /* How long to wait (in milliseconds) if there are no acks
     before sending one more datagram */
  unsigned int timeout_ms( void );
};

#endif
