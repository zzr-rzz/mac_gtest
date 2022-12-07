#include "ft_dsl_suit.h"
#include "ft_exception.h"
#include "ft_msg_builder.h"
#include "ft_msg_asserter.h"

FTESTING_NS_BEGIN

DECL_FT_SUIT(mac_recieve)
{
    FT_SETUP()
    {
        FT_ASSERT(TRUE);
    }

    FT_TEARDOWN()
    {
        
    }

};


DEF_ACTION(net_send_one_pk)
{
    SEND_MSG(net, one_net_pk_builder);
}

DEF_ACTION(phy_deliver_one_beacon)
{
    SEND_MSG(phy, one_phy_pk_builder, set_phy_frame, set_beacon);
}

DEF_ACTION(phy_deliver_one_data)
{
    SEND_MSG(phy, one_phy_pk_builder, set_phy_frame, set_data_frame);
}

DEF_ACTION(net_receive_one_pk)
{
    RECEIVE_MSG(net, net_receive_beacon_asserter);
}

DEF_ACTION(net_receive_data_pk)
{
    RECEIVE_MSG(net, net_receive_data_asserter);
}

TEST_F(mac_recieve, both_net_and_phy_send_data)
{
    INVOKE_ACTION(phy_deliver_one_beacon);
    INVOKE_ACTION(phy_deliver_one_data);
    INVOKE_ACTION(net_receive_data_pk);
}

// TEST_F(mac_recieve, both_net_and_phy_send_data2)
// {
//     INVOKE_ACTION(net_send_one_pk);
//     INVOKE_ACTION(net_receive_one_pk);
//     INVOKE_ACTION(phy_deliver_one_beacon);
// }

FTESTING_NS_END

