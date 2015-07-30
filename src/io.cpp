#include "io.h"
#include <iostream>
#include <map>

void Error(const std::string& msg)
{
	std::cerr << "ERROR: " << msg << "\n";
}

void Warning(const std::string& msg)
{
	std::cout << "Warning: " << msg << "\n";
}

void Inform(const std::string& msg)
{
	std::cout << ":- " << msg << "\n";
}

std::string appendNameToPath(const std::string& name, const std::string& path)
{
	if (path.size() == 0)
		return name;

	//If separator already exists, just add
	if (path.back() == '\\' || path.back() == '/')
		return path + name;
	else
#ifdef _WIN32
		return path + "\\" + name;
#else
		return path + "/" + name;
#endif
}

static std::map<long, const char*> edsErrorMapping
{
	{ 0x00000000L,"EDS_ERR_OK" },
	{ 0x00000001L,"EDS_ERR_UNIMPLEMENTED" },
	{ 0x00000002L,"EDS_ERR_INTERNAL_ERROR" },
	{ 0x00000003L,"EDS_ERR_MEM_ALLOC_FAILED" },
	{ 0x00000004L,"EDS_ERR_MEM_FREE_FAILED" },
	{ 0x00000005L,"EDS_ERR_OPERATION_CANCELLED" },
	{ 0x00000006L,"EDS_ERR_INCOMPATIBLE_VERSION" },
	{ 0x00000007L,"EDS_ERR_NOT_SUPPORTED" },
	{ 0x00000008L,"EDS_ERR_UNEXPECTED_EXCEPTION" },
	{ 0x00000009L,"EDS_ERR_PROTECTION_VIOLATION" },
	{ 0x0000000AL,"EDS_ERR_MISSING_SUBCOMPONENT" },
	{ 0x0000000BL,"EDS_ERR_SELECTION_UNAVAILABLE" },
	{ 0x00000020L,"EDS_ERR_FILE_IO_ERROR" },
	{ 0x00000021L,"EDS_ERR_FILE_TOO_MANY_OPEN" },
	{ 0x00000022L,"EDS_ERR_FILE_NOT_FOUND" },
	{ 0x00000023L,"EDS_ERR_FILE_OPEN_ERROR" },
	{ 0x00000024L,"EDS_ERR_FILE_CLOSE_ERROR" },
	{ 0x00000025L,"EDS_ERR_FILE_SEEK_ERROR" },
	{ 0x00000026L,"EDS_ERR_FILE_TELL_ERROR" },
	{ 0x00000027L,"EDS_ERR_FILE_READ_ERROR" },
	{ 0x00000028L,"EDS_ERR_FILE_WRITE_ERROR" },
	{ 0x00000029L,"EDS_ERR_FILE_PERMISSION_ERROR" },
	{ 0x0000002AL,"EDS_ERR_FILE_DISK_FULL_ERROR" },
	{ 0x0000002BL,"EDS_ERR_FILE_ALREADY_EXISTS" },
	{ 0x0000002CL,"EDS_ERR_FILE_FORMAT_UNRECOGNIZED" },
	{ 0x0000002DL,"EDS_ERR_FILE_DATA_CORRUPT" },
	{ 0x0000002EL,"EDS_ERR_FILE_NAMING_NA" },
	{ 0x00000040L,"EDS_ERR_DIR_NOT_FOUND" },
	{ 0x00000041L,"EDS_ERR_DIR_IO_ERROR" },
	{ 0x00000042L,"EDS_ERR_DIR_ENTRY_NOT_FOUND" },
	{ 0x00000043L,"EDS_ERR_DIR_ENTRY_EXISTS" },
	{ 0x00000044L,"EDS_ERR_DIR_NOT_EMPTY" },
	{ 0x00000050L,"EDS_ERR_PROPERTIES_UNAVAILABLE" },
	{ 0x00000051L,"EDS_ERR_PROPERTIES_MISMATCH" },
	{ 0x00000053L,"EDS_ERR_PROPERTIES_NOT_LOADED" },
	{ 0x00000060L,"EDS_ERR_INVALID_PARAMETER" },
	{ 0x00000061L,"EDS_ERR_INVALID_HANDLE" },
	{ 0x00000062L,"EDS_ERR_INVALID_POINTER" },
	{ 0x00000063L,"EDS_ERR_INVALID_INDEX" },
	{ 0x00000064L,"EDS_ERR_INVALID_LENGTH" },
	{ 0x00000065L,"EDS_ERR_INVALID_FN_POINTER" },
	{ 0x00000066L,"EDS_ERR_INVALID_SORT_FN" },
	{ 0x00000080L,"EDS_ERR_DEVICE_NOT_FOUND" },
	{ 0x00000081L,"EDS_ERR_DEVICE_BUSY" },
	{ 0x00000082L,"EDS_ERR_DEVICE_INVALID" },
	{ 0x00000083L,"EDS_ERR_DEVICE_EMERGENCY" },
	{ 0x00000084L,"EDS_ERR_DEVICE_MEMORY_FULL" },
	{ 0x00000085L,"EDS_ERR_DEVICE_INTERNAL_ERROR" },
	{ 0x00000086L,"EDS_ERR_DEVICE_INVALID_PARAMETER" },
	{ 0x00000087L,"EDS_ERR_DEVICE_NO_DISK" },
	{ 0x00000088L,"EDS_ERR_DEVICE_DISK_ERROR" },
	{ 0x00000089L,"EDS_ERR_DEVICE_CF_GATE_CHANGED" },
	{ 0x0000008AL,"EDS_ERR_DEVICE_DIAL_CHANGED" },
	{ 0x0000008BL,"EDS_ERR_DEVICE_NOT_INSTALLED" },
	{ 0x0000008CL,"EDS_ERR_DEVICE_STAY_AWAKE" },
	{ 0x0000008DL,"EDS_ERR_DEVICE_NOT_RELEASED" },
	{ 0x000000A0L,"EDS_ERR_STREAM_IO_ERROR" },
	{ 0x000000A1L,"EDS_ERR_STREAM_NOT_OPEN" },
	{ 0x000000A2L,"EDS_ERR_STREAM_ALREADY_OPEN" },
	{ 0x000000A3L,"EDS_ERR_STREAM_OPEN_ERROR" },
	{ 0x000000A4L,"EDS_ERR_STREAM_CLOSE_ERROR" },
	{ 0x000000A5L,"EDS_ERR_STREAM_SEEK_ERROR" },
	{ 0x000000A6L,"EDS_ERR_STREAM_TELL_ERROR" },
	{ 0x000000A7L,"EDS_ERR_STREAM_READ_ERROR" },
	{ 0x000000A8L,"EDS_ERR_STREAM_WRITE_ERROR" },
	{ 0x000000A9L,"EDS_ERR_STREAM_PERMISSION_ERROR" },
	{ 0x000000AAL,"EDS_ERR_STREAM_COULDNT_BEGIN_THREAD" },
	{ 0x000000ABL,"EDS_ERR_STREAM_BAD_OPTIONS" },
	{ 0x000000ACL,"EDS_ERR_STREAM_END_OF_STREAM" },
	{ 0x000000C0L,"EDS_ERR_COMM_PORT_IS_IN_USE" },
	{ 0x000000C1L,"EDS_ERR_COMM_DISCONNECTED" },
	{ 0x000000C2L,"EDS_ERR_COMM_DEVICE_INCOMPATIBLE" },
	{ 0x000000C3L,"EDS_ERR_COMM_BUFFER_FULL" },
	{ 0x000000C4L,"EDS_ERR_COMM_USB_BUS_ERR" },
	{ 0x000000D0L,"EDS_ERR_USB_DEVICE_LOCK_ERROR" },
	{ 0x000000D1L,"EDS_ERR_USB_DEVICE_UNLOCK_ERROR" },
	{ 0x000000E0L,"EDS_ERR_STI_UNKNOWN_ERROR" },
	{ 0x000000E1L,"EDS_ERR_STI_INTERNAL_ERROR" },
	{ 0x000000E2L,"EDS_ERR_STI_DEVICE_CREATE_ERROR" },
	{ 0x000000E3L,"EDS_ERR_STI_DEVICE_RELEASE_ERROR" },
	{ 0x000000E4L,"EDS_ERR_DEVICE_NOT_LAUNCHED" },
	{ 0x000000F0L,"EDS_ERR_ENUM_NA" },
	{ 0x000000F1L,"EDS_ERR_INVALID_FN_CALL" },
	{ 0x000000F2L,"EDS_ERR_HANDLE_NOT_FOUND" },
	{ 0x000000F3L,"EDS_ERR_INVALID_ID" },
	{ 0x000000F4L,"EDS_ERR_WAIT_TIMEOUT_ERROR" },
	{ 0x00002003L,"EDS_ERR_SESSION_NOT_OPEN" },
	{ 0x00002004L,"EDS_ERR_INVALID_TRANSACTIONID" },
	{ 0x00002007L,"EDS_ERR_INCOMPLETE_TRANSFER" },
	{ 0x00002008L,"EDS_ERR_INVALID_STRAGEID" },
	{ 0x0000200AL,"EDS_ERR_DEVICEPROP_NOT_SUPPORTED" },
	{ 0x0000200BL,"EDS_ERR_INVALID_OBJECTFORMATCODE" },
	{ 0x00002011L,"EDS_ERR_SELF_TEST_FAILED" },
	{ 0x00002012L,"EDS_ERR_PARTIAL_DELETION" },
	{ 0x00002014L,"EDS_ERR_SPECIFICATION_BY_FORMAT_UNSUPPORTED" },
	{ 0x00002015L,"EDS_ERR_NO_VALID_OBJECTINFO" },
	{ 0x00002016L,"EDS_ERR_INVALID_CODE_FORMAT" },
	{ 0x00002017L,"EDS_ERR_UNKNOWN_VENDOR_CODE" },
	{ 0x00002018L,"EDS_ERR_CAPTURE_ALREADY_TERMINATED" },
	{ 0x0000201AL,"EDS_ERR_INVALID_PARENTOBJECT" },
	{ 0x0000201BL,"EDS_ERR_INVALID_DEVICEPROP_FORMAT" },
	{ 0x0000201CL,"EDS_ERR_INVALID_DEVICEPROP_VALUE" },
	{ 0x0000201EL,"EDS_ERR_SESSION_ALREADY_OPEN" },
	{ 0x0000201FL,"EDS_ERR_TRANSACTION_CANCELLED" },
	{ 0x00002020L,"EDS_ERR_SPECIFICATION_OF_DESTINATION_UNSUPPORTED" },
	{ 0x0000A001L,"EDS_ERR_UNKNOWN_COMMAND" },
	{ 0x0000A005L,"EDS_ERR_OPERATION_REFUSED" },
	{ 0x0000A006L,"EDS_ERR_LENS_COVER_CLOSE" },
	{ 0x0000A101L,"EDS_ERR_LOW_BATTERY" },
	{ 0x0000A102L,"EDS_ERR_OBJECT_NOTREADY" },
	{ 0x00008D01L,"EDS_ERR_TAKE_PICTURE_AF_NG" },
	{ 0x00008D02L,"EDS_ERR_TAKE_PICTURE_RESERVED" },
	{ 0x00008D03L,"EDS_ERR_TAKE_PICTURE_MIRROR_UP_NG" },
	{ 0x00008D04L,"EDS_ERR_TAKE_PICTURE_SENSOR_CLEANING_NG" },
	{ 0x00008D05L,"EDS_ERR_TAKE_PICTURE_SILENCE_NG" },
	{ 0x00008D06L,"EDS_ERR_TAKE_PICTURE_NO_CARD_NG" },
	{ 0x00008D07L,"EDS_ERR_TAKE_PICTURE_CARD_NG" },
	{ 0x00008D08L,"EDS_ERR_TAKE_PICTURE_CARD_PROTECT_NG" },
	{ 0x000000F5L,"EDS_ERR_LAST_GENERIC_ERROR_PLUS_ONE" }
};


std::string EdsCodeToString(long code)
{
	return edsErrorMapping[code];
}