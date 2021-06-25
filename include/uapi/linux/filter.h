<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Linux Socket Filter Data Structures
 */

#अगर_अघोषित _UAPI__LINUX_FILTER_H__
#घोषणा _UAPI__LINUX_FILTER_H__

#समावेश <linux/compiler.h>
#समावेश <linux/types.h>
#समावेश <linux/bpf_common.h>

/*
 * Current version of the filter code architecture.
 */
#घोषणा BPF_MAJOR_VERSION 1
#घोषणा BPF_MINOR_VERSION 1

/*
 *	Try and keep these values and काष्ठाures similar to BSD, especially
 *	the BPF code definitions which need to match so you can share filters
 */
 
काष्ठा sock_filter अणु	/* Filter block */
	__u16	code;   /* Actual filter code */
	__u8	jt;	/* Jump true */
	__u8	jf;	/* Jump false */
	__u32	k;      /* Generic multiuse field */
पूर्ण;

काष्ठा sock_fprog अणु	/* Required क्रम SO_ATTACH_FILTER. */
	अचिन्हित लघु		len;	/* Number of filter blocks */
	काष्ठा sock_filter __user *filter;
पूर्ण;

/* ret - BPF_K and BPF_X also apply */
#घोषणा BPF_RVAL(code)  ((code) & 0x18)
#घोषणा         BPF_A           0x10

/* misc */
#घोषणा BPF_MISCOP(code) ((code) & 0xf8)
#घोषणा         BPF_TAX         0x00
#घोषणा         BPF_TXA         0x80

/*
 * Macros क्रम filter block array initializers.
 */
#अगर_अघोषित BPF_STMT
#घोषणा BPF_STMT(code, k) अणु (अचिन्हित लघु)(code), 0, 0, k पूर्ण
#पूर्ण_अगर
#अगर_अघोषित BPF_JUMP
#घोषणा BPF_JUMP(code, k, jt, jf) अणु (अचिन्हित लघु)(code), jt, jf, k पूर्ण
#पूर्ण_अगर

/*
 * Number of scratch memory words क्रम: BPF_ST and BPF_STX
 */
#घोषणा BPF_MEMWORDS 16

/* RATIONALE. Negative offsets are invalid in BPF.
   We use them to reference ancillary data.
   Unlike पूर्णांकroduction new inकाष्ठाions, it करोes not अवरोध
   existing compilers/optimizers.
 */
#घोषणा SKF_AD_OFF    (-0x1000)
#घोषणा SKF_AD_PROTOCOL 0
#घोषणा SKF_AD_PKTTYPE 	4
#घोषणा SKF_AD_IFINDEX 	8
#घोषणा SKF_AD_NLATTR	12
#घोषणा SKF_AD_NLATTR_NEST	16
#घोषणा SKF_AD_MARK 	20
#घोषणा SKF_AD_QUEUE	24
#घोषणा SKF_AD_HATYPE	28
#घोषणा SKF_AD_RXHASH	32
#घोषणा SKF_AD_CPU	36
#घोषणा SKF_AD_ALU_XOR_X	40
#घोषणा SKF_AD_VLAN_TAG	44
#घोषणा SKF_AD_VLAN_TAG_PRESENT 48
#घोषणा SKF_AD_PAY_OFFSET	52
#घोषणा SKF_AD_RANDOM	56
#घोषणा SKF_AD_VLAN_TPID	60
#घोषणा SKF_AD_MAX	64

#घोषणा SKF_NET_OFF	(-0x100000)
#घोषणा SKF_LL_OFF	(-0x200000)

#घोषणा BPF_NET_OFF	SKF_NET_OFF
#घोषणा BPF_LL_OFF	SKF_LL_OFF

#पूर्ण_अगर /* _UAPI__LINUX_FILTER_H__ */
