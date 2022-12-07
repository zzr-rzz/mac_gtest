#include "ft_msg_role.h"
#include "ft_exception.h"
#include <stdlib.h>
#include "pub_msg_id_def.h"
FTESTING_NS_BEGIN

void* basic_builder_t::build(fake_subsys_t& _system)
{
    void* msg = do_build(_system);
    for (auto p : m_list)
    {
        if (FT_OK != p(msg, _system))
        {
            free(msg);
            msg = NULL;
            break;
        } 
    }
    return msg;
}

void basic_asserter_t::assertion(void* msg, fake_subsys_t& _system) const
{
    FT_ASSERT(NULL != msg);
    if (0 == m_list.size())
    {
        do_assert(msg, _system);
    }
    for (auto p : m_list)
    {
        p(msg, _system);
    }
}

FTESTING_NS_END
