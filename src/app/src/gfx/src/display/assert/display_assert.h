/*
 * display_assert.h
 *
 *  Created on: 1 Aug 2022
 *      Author: a5126135
 */

#ifndef DISPLAY_ASSERT_DISPLAY_ASSERT_H_
#define DISPLAY_ASSERT_DISPLAY_ASSERT_H_

#define ASSERT_DEBUG

static void disp_assert_func (const char * file, int line, const char * func, const char * expr)
{
    (void)file;
    (void)line;
    (void)func;
    (void)expr;

    while (1)
    {
        /* Do nothing. */
    }
}

# ifndef __ASSERT_FUNC
  /* Use g++'s demangled names in C++.  */
#  if defined __cplusplus && defined __GNUC__
#   define __ASSERT_FUNC __PRETTY_FUNCTION__

  /* C99 requires the use of __func__.  */
#  elif __STDC_VERSION__ >= 199901L
#   define __ASSERT_FUNC __func__

  /* Older versions of gcc don't have __func__ but can use __FUNCTION__.  */
#  elif __GNUC__ >= 2
#   define __ASSERT_FUNC __FUNCTION__

  /* failed to detect __func__ support.  */
#  else
#   define __ASSERT_FUNC ((char *) 0)
#  endif
# endif /* !__ASSERT_FUNC */

#define assert_impl(__e) ((__e) ? (void)0 : disp_assert_func (__FILE__, __LINE__, \
						       __ASSERT_FUNC, #__e))

#if defined(ASSERT_DEBUG)
#define DISPLAY_ASSERT_VOID(_e)	assert_impl(_e)
#define DISPLAY_ASSERT(_e, ret)	assert_impl(_e)

#elif defined(ASSERT_NONE)
#define DISPLAY_ASSERT_VOID(_e, ret)
#define DISPLAY_ASSERT(_e, ret)

#else
#define DISPLAY_ASSERT_VOID(_e)					\
    {                                                   \
        if ((_e))                                       \
        {                                               \
            (void) 0;                  /* Do nothing */ \
        }                                               \
        else                                            \
        {                                               \
            return;                                		\
        }                                               \
    }

#define DISPLAY_ASSERT(_e, ret)					\
    {                                                   \
        if ((_e))                                       \
        {                                               \
            (void) 0;                  /* Do nothing */ \
        }                                               \
        else                                            \
        {                                               \
            return ret;                           		\
        }                                               \
    }

#endif

#endif /* DISPLAY_ASSERT_DISPLAY_ASSERT_H_ */
