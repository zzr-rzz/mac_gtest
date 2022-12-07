#include <stdlib.h>
#include "ft_sys_role.h"
#include "ft_msg_builder.h"
#include "mac_phy_api.h"
#include "mac_frame_def.h"
#include "mem_check.h"
#include "ft_oss.h"

FTESTING_NS_BEGIN

IMP_FT_MSG_BUILDER(one_net_pk_builder)
{
    void* msg = ALLOC_MEM(2000);
    m_tno = NET_TNO;
    // m_timeout = 0;
    return msg;
};

IMP_FT_MSG_BUILDER(one_phy_pk_builder)
{
    U16 len = sizeof(phy2mac_data_t) + 100;
    phy2mac_data_t *msg = (phy2mac_data_t*)ALLOC_MEM(len);

    msg->head.magic = MSG_MAGIC_DIGIT;
    msg->head.msg_id = EV_PHY2MAC_MAC_FRAME_MSG;
    msg->head.len = len;
    m_tno = PHY_TNO;
    return msg;
};


IMP_FT_MSG_SET(set_phy_frame)
{
    phy2mac_data_t *msg = (phy2mac_data_t*)p_data;

    msg->head.magic = MSG_MAGIC_DIGIT;
    msg->head.msg_id = EV_PHY2MAC_MAC_FRAME_MSG;

    return FT_OK;
}

IMP_FT_MSG_SET(set_beacon)
{
    phy2mac_data_t *msg = (phy2mac_data_t*)p_data;
    U8* frame_data = msg->rx_data;

    SET_CTRL_TYPE(frame_data, FRAME_CTR_TYPE_MANAGE);
    SET_CTRL_SUBTYPE(frame_data, FRAME_MANAGE_SUB_TYPE_BEACON);
    return FT_OK;
}

IMP_FT_MSG_SET(set_data_frame)
{
    phy2mac_data_t *msg = (phy2mac_data_t*)p_data;
    U8* frame_data = msg->rx_data;
    SET_COMM_MAC_HEAD(frame_data, FRAME_CTR_TYPE_DATA, FRAME_DATA_SUB_TYPE_DATA, 10, 2660, 12, 1);
    return FT_OK;
}

FTESTING_NS_END
