#ifndef __BLUEGRASS_SDP_CONTROLLER__
#define __BLUEGRASS_SDP_CONTROLLER__

#include <vector>
#include <string>

#include "bluegrass/bluetooth.hpp"

namespace bluegrass {

	/*
	 * Class sdp_controller may be used to access the local device SDP server 
	 * or to access the SDP server on a remote device. The default argument of
	 * this class connects to the local device SDP server, but a programmer may
	 * pass the Bluetooth address of remote device to access the device's SDP
	 * server. On destruction the class object closes the SDP server session it
	 * represents.
	 */
	class sdp_controller {
	public:
		/*
		 * Description: sdp_controller() constructs an SDP session with the 
		 * local SDP server of the device running the program. Only 
		 * register_service (will be) invokable by an sdp_controller constructed
		 * in this way.
		 */
		sdp_controller();
		
		/*
		 * Description: sdp_controller(bdaddr_t) constructs an SDP session with 
		 * a remote Bluetooth device's SDP server. Only service_search (will be)
		 * invokable by an sdp_controller object constructed in this way.
		 */
		sdp_controller(bdaddr_t);
		
		sdp_controller(const sdp_controller&) = delete;
		sdp_controller(sdp_controller&&) = default;
		sdp_controller& operator=(const sdp_controller&) = delete;
		sdp_controller& operator=(sdp_controller&&) = default;
		
		// will also unregister all services associated with this sdp session
		~sdp_controller();
		
		/*
		 * Function service_search has two parameters:
		 *	 const service - the service ID to search for (proto and port are not used)
		 *	 std::vector<service>& - container to store the found services
		 *
		 * Description: service_search performs a search of services matching
		 * the argument "svc" service on the remote device's SDP server. On 
		 * return the "resps" vector is filled with matching services. The 
		 * majority of code was ported from Albert Huang's: "The Use of 
		 * Bluetooth in Linux and Location aware Computing"
		 */
		void service_search(const service&, std::vector<service>&) const;
		
		/*
		 * Function service_search has four parameters:
		 *	 const service - the service to register
		 *	 const std::string& - name of service
		 *   const std::string& - provider of service
		 *   const std::string& - description of service
		 *
		 * Description: register_search constructs a service record and registers 
		 * that service on the Bluetooth devices local SDP server. The majority 
		 * of code was ported from Albert Huang's: "The Use of Bluetooth in Linux 
		 * and Location aware Computing"
		 */
		bool register_service(const service&, const std::string&, const std::string&, const std::string&);
	
	private:
		sdp_session_t* session_;
	};
	
} // namespace bluegrass 

#endif