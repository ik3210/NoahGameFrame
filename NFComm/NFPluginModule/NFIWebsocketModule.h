// -------------------------------------------------------------------------
//    @FileName			:    NFIWebsocketModule.h
//    @Author           :    Stone.xin<xinxinst@163.com>
//    @Date             :    2016-12-22
//    @Module           :    NFIWebsocketModule
//    @Desc             :
// -------------------------------------------------------------------------
#ifndef NFI_WEBSOCKET_MODULE_H__
#define NFI_WEBSOCKET_MODULE_H__

#include "NFComm/NFNetPlugin/NFIWS.h"
#include "NFIModule.h"

class NFIWebsocketModule : public NFIModule
{
public:
	template<typename BaseType>
	void SetReceiveCallBack(BaseType* pBaseType, void (BaseType::*handleRecieve)(websocketpp::connection_hdl, const std::string&, const NF_WS_MSG_DATA_TYPE))
	{
		NF_WS_MSG_CALL_BACK functor = std::bind(handleRecieve, pBaseType, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);
		NF_WS_MSG_CALL_BACK_PTR functorPtr(new NF_WS_MSG_CALL_BACK(functor));

		SetReceiveCallBack(functorPtr);
	}

	template<typename BaseType>
	void SetEventCallBack(BaseType* pBaseType, void (BaseType::*handleEvent)(websocketpp::connection_hdl, NF_WS_EVENT))
	{
		NF_WS_EVENT_CALL_BACK functor = std::bind(handleEvent, pBaseType, std::placeholders::_1, std::placeholders::_2);
		NF_WS_EVENT_CALL_BACK_PTR functorPtr(new NF_WS_EVENT_CALL_BACK(functor));

		SetEventCallBack(functorPtr);
	}
	
	virtual int Initialization(const unsigned int nMaxClient, const unsigned short nPort, const int nCpuCount = 4) = 0;

	virtual bool SendMsgToAllClient(const char* msg, const uint32_t nLen, NF_WS_MSG_DATA_TYPE msg_data_type = TEXT) = 0;
	virtual bool SendMsgToClient(const char* msg, const uint32_t nLen, const std::vector<websocketpp::connection_hdl>& conn_list, NF_WS_MSG_DATA_TYPE msg_data_type = TEXT) = 0;
	virtual bool SendMsgToClient(const char* msg, const uint32_t nLen, websocketpp::connection_hdl conn, NF_WS_MSG_DATA_TYPE msg_data_type = TEXT) = 0;

protected:

	virtual void SetReceiveCallBack(NF_WS_MSG_CALL_BACK_PTR functorPtr) = 0;
	virtual void SetEventCallBack(NF_WS_EVENT_CALL_BACK_PTR functorPtr) = 0;
};

#endif // NFI_WEBSOCKET_MODULE_H__