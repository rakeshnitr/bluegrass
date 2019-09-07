#ifndef __BLUETOOTH__
#define __BLUETOOTH__

/*
 * Including bluetooth.hpp includes all the Bluetooth libraries associated
 * with the Blue-Z 5.50 library. If this file is included in a program then 
 * the Blue-Z library (-lbluetooth) must be linked with the program. 
 * These header files are located in the directory: "/usr/include/bluetooth".
 */
#include <bluetooth/bluetooth.h>
#include <bluetooth/bnep.h>
#include <bluetooth/cmtp.h>
#include <bluetooth/hci.h>
#include <bluetooth/hci_lib.h>
#include <bluetooth/hidp.h>
#include <bluetooth/l2cap.h>
#include <bluetooth/rfcomm.h>
#include <bluetooth/sco.h>
#include <bluetooth/sdp.h>
#include <bluetooth/sdp_lib.h>

#include <iostream>

namespace bluegrass {
	
	/*
	 * Description: proto_t is used to specify the Bluteooth protocol used by 
	 * sockets and address.
	 */
	enum proto_t {
		L2CAP = L2CAP_UUID,
		RFCOMM = RFCOMM_UUID,
	};
	
	/*
	 * Struct template has one template parameter
	 *     P - the Bluetooth socket protocol 
	 * 
	 * Description: address is a simple struct which wraps a socket address
	 * and int storing the length of the socket address. This struct is used
	 * to the address of a socket class to capture the address to send data to
	 * or where data is comming from.
	 */
	template <proto_t P>
	struct address {
		typename std::conditional_t<P == L2CAP, sockaddr_l2, sockaddr_rc> addr;
		socklen_t len;
	};
	
	/*
	 * Struct to package information about a Bluetooth service. service struct
	 * has service id, Bluetooth protocol, and port number.
	 */
	struct service {
		uint16_t id;
		proto_t proto;
		uint16_t port;
	};
	
	/*
	 * Struct to package information from an HCI inquiry. This struct will grow
	 * as more functionality is added.
	 */
	struct device {
		bdaddr_t addr;
		uint16_t offset;
	};
	
	/*
	 * Description: Prints a human readable Bluetooth device address 
	 */
	std::ostream& operator<<(std::ostream& out, const bdaddr_t& ba)  
	{
		std::ios_base::fmtflags ff(out.flags());
		out << std::hex << std::uppercase 
		<< (uint32_t) ba.b[5] << ':' << (uint32_t) ba.b[4] << ':' << (uint32_t) ba.b[3] 
		<< ':' 
		<< (uint32_t) ba.b[2] << ':' << (uint32_t) ba.b[1] << ':' << (uint32_t) ba.b[0];
		out.flags(ff);
		
		return out;
	}
	
}

#endif
