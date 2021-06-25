<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _TOOLS_LINUX_TYPES_H_
#घोषणा _TOOLS_LINUX_TYPES_H_

#समावेश <stdbool.h>
#समावेश <मानकघोष.स>
#समावेश <मानक_निवेशt.h>

#अगर_अघोषित __SANE_USERSPACE_TYPES__
#घोषणा __SANE_USERSPACE_TYPES__	/* For PPC64, to get LL64 types */
#पूर्ण_अगर

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/posix_types.h>

काष्ठा page;
काष्ठा kmem_cache;

प्रकार क्रमागत अणु
	GFP_KERNEL,
	GFP_ATOMIC,
	__GFP_HIGHMEM,
	__GFP_HIGH
पूर्ण gfp_t;

/*
 * We define u64 as uपूर्णांक64_t क्रम every architecture
 * so that we can prपूर्णांक it with "%"PRIx64 without getting warnings.
 *
 * प्रकार __u64 u64;
 * प्रकार __s64 s64;
 */
प्रकार uपूर्णांक64_t u64;
प्रकार पूर्णांक64_t s64;

प्रकार __u32 u32;
प्रकार __s32 s32;

प्रकार __u16 u16;
प्रकार __s16 s16;

प्रकार __u8  u8;
प्रकार __s8  s8;

#अगर_घोषित __CHECKER__
#घोषणा __bitwise__ __attribute__((bitwise))
#अन्यथा
#घोषणा __bitwise__
#पूर्ण_अगर
#घोषणा __bitwise __bitwise__

#घोषणा __क्रमce
#घोषणा __user
#घोषणा __must_check
#घोषणा __cold

प्रकार __u16 __bitwise __le16;
प्रकार __u16 __bitwise __be16;
प्रकार __u32 __bitwise __le32;
प्रकार __u32 __bitwise __be32;
प्रकार __u64 __bitwise __le64;
प्रकार __u64 __bitwise __be64;

प्रकार __u16 __bitwise __sum16;
प्रकार __u32 __bitwise __wsum;

प्रकार काष्ठा अणु
	पूर्णांक counter;
पूर्ण atomic_t;

#अगर_अघोषित __aligned_u64
# define __aligned_u64 __u64 __attribute__((aligned(8)))
#पूर्ण_अगर

काष्ठा list_head अणु
	काष्ठा list_head *next, *prev;
पूर्ण;

काष्ठा hlist_head अणु
	काष्ठा hlist_node *first;
पूर्ण;

काष्ठा hlist_node अणु
	काष्ठा hlist_node *next, **pprev;
पूर्ण;

#पूर्ण_अगर /* _TOOLS_LINUX_TYPES_H_ */
