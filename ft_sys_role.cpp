#include "ft_sys_role.h"
#include "ft_msg_role.h"

#include "ft_exception.h"
#include "mem_check.h"
#include "oss_comm.h"
#include "ft_oss.h"

FTESTING_NS_BEGIN

int fake_subsys_t::send(basic_builder_t& builder)
{
    U32 result = OSS_SUCCESS;
    U8 *msg = (U8*)builder.build(*this);
    head_t* head = (head_t*)msg;
    FT_ASSERT(NULL != msg);
    result = oss_sendtocore(msg, head->len, head->msg_id, builder.m_tno, MAC_TNO);
    FREE_MEM(msg);
    return result == OSS_SUCCESS ? FT_OK : FT_ERROR;
}

#define FT_WAIT_MOMENT(count) \
{\
    count++;\
    if (count > 100000)\
    {\
        break;\
    }\
}

void fake_subsys_t::wait(const basic_asserter_t& asserter)
{
    t_msg *msg = PNULL;
    //int  count = 0;
    do 
    {
        msg = (t_msg*)oss_other_rcv_msg();
        if (PNULL != msg )
        {
            break;
        }  
        //FT_WAIT_MOMENT(count);
    }while (1);
      
    asserter.assertion(msg->data, *this);
    FREE_MEM(msg->data);
    FREE_MEM(msg);
}

bool fake_subsys_t::peek(const U16& msg_id)
{
    // return ring_buf_find(received_from, msg_id);
    return TRUE;
}

FTESTING_NS_END
