#include "ft_frame.h"
#include "ft_dsl_suit.h"



FTESTING_NS_BEGIN

void ft_fixture_t::SetUp()
{
    do_setup();
}

void ft_fixture_t::TearDown()
{
    do_teardown();
    usleep(100000);
}

FTESTING_NS_END
