#include <gtest/gtest.h>
#include <pthread.h>
#include "ft_exception.h"
#include "pub_msg_id_def.h"
#include "mem_check.h"
#include "ft_oss.h"
#include "ft_log.h"

extern void mac_entry(U8* ptmsg, U16 msgid, U32 msglen);

using namespace ftesting;

namespace
{
    static int g_task_switch = 0;
    void set_task_switch(int opt)
    {
        g_task_switch = opt;
    }

    static void* mac_ctrl_thread_run(void *arg)
    {
        U8* p_msg = PNULL;
        t_msg *head = PNULL;
        t_msg msg;
        g_task_switch = 1;
        ft_ini_ring();
        msg.data = (BYTE*)ALLOC_MEM(10);
        mac_entry((U8*)&msg.data, EV_STARTUP, 10);
        while (g_task_switch)
        { 
            p_msg = oss_mac_rcv_msg();
            if (PNULL != p_msg)
            {
                head = (t_msg *)p_msg;
                if (MAC_TNO == head->rcvtno)
                {
                    mac_entry((U8*)(&head->data), head->msgid, head->msglen);
                }
                else
                {
                    FT_LOG(LOG_ERROR, DEFAULT_ID, "Unexpect msg rcvtno[%d] id[%d]", head->rcvtno, head->msgid);
                }
                FREE_MEM(p_msg);
            } 
        }
        ft_destry_ring();
        return arg;
    }

    static void mac_ctrl_thread_init(pthread_t& t_id)
    {
        int err;
        pthread_t temp;
        err = pthread_create(&temp, NULL, mac_ctrl_thread_run, NULL);
        if (err != 0)
        {
            exit(err);
        }
        t_id = temp;
    }

    struct mesh_mac_env : testing::Environment
    {
        pthread_t mac_ctrl_thread_id;
        virtual void SetUp()
        {
            set_mem_leak_check_flag(1);
            mac_ctrl_thread_init(mac_ctrl_thread_id);
            usleep(50000);
        }
        virtual void TearDown()
        {
            set_task_switch(0);
            pthread_join(mac_ctrl_thread_id, NULL);
            FT_ASSERT(0 == mem_leak_check_print());
            usleep(50000);
        }
    };
}


int main(int argc,char *argv[])
{
    try
    {
        testing::GTEST_FLAG(break_on_failure) = 1;
        testing::InitGoogleTest(&argc, argv);

        // append --gtest_verbose into google test option list when output detail log.
        // initGlobalSwitch(testing::GTEST_FLAG(color) != "no", testing::GTEST_FLAG(verbose));
        testing::AddGlobalTestEnvironment(new mesh_mac_env());

        int ret = RUN_ALL_TESTS();

        return ret;
    }
    catch (const exception_t& e)
    {
        printf("%s", e.what());	
        return 1;
    }
    catch (const std::exception& e)
    {
        printf("%s", e.what());	
        return 2;
    }
    catch (...)
    {
        printf("unknown runntime execption\n");	
        return 3;
    }

    return 4;
}


