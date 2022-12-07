#include "ft_sys_role.h"
#include "ft_msg_asserter.h"
#include "ft_exception.h"
#include "net_mac_api.h"
#include "mem_check.h"
FTESTING_NS_BEGIN

IMP_FT_MSG_ASSERTER(net_receive_beacon_asserter)
{
    mac2net_data_t* msg = (mac2net_data_t*)_msg;
    FT_ASSERT(EV_MAC2NET_BEACON == msg->head.msg_id);
}

IMP_FT_MSG_ASSERTER(net_receive_data_asserter)
{
    mac2net_data_t* msg = (mac2net_data_t*)_msg;
    FT_ASSERT(EV_MAC2NET_DATA == msg->head.msg_id);
}

FTESTING_NS_END
