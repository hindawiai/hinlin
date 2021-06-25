<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _LINUX_GSMMUX_H
#घोषणा _LINUX_GSMMUX_H

#समावेश <linux/अगर.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/types.h>

काष्ठा gsm_config
अणु
	अचिन्हित पूर्णांक adaption;
	अचिन्हित पूर्णांक encapsulation;
	अचिन्हित पूर्णांक initiator;
	अचिन्हित पूर्णांक t1;
	अचिन्हित पूर्णांक t2;
	अचिन्हित पूर्णांक t3;
	अचिन्हित पूर्णांक n2;
	अचिन्हित पूर्णांक mru;
	अचिन्हित पूर्णांक mtu;
	अचिन्हित पूर्णांक k;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक unused[8];		/* Padding क्रम expansion without
					   अवरोधing stuff */
पूर्ण;

#घोषणा GSMIOC_GETCONF		_IOR('G', 0, काष्ठा gsm_config)
#घोषणा GSMIOC_SETCONF		_IOW('G', 1, काष्ठा gsm_config)

काष्ठा gsm_netconfig अणु
	अचिन्हित पूर्णांक adaption;  /* Adaption to use in network mode */
	अचिन्हित लघु protocol;/* Protocol to use - only ETH_P_IP supported */
	अचिन्हित लघु unused2;
	अक्षर अगर_name[IFNAMSIZ];	/* पूर्णांकerface name क्रमmat string */
	__u8 unused[28];        /* For future use */
पूर्ण;

#घोषणा GSMIOC_ENABLE_NET      _IOW('G', 2, काष्ठा gsm_netconfig)
#घोषणा GSMIOC_DISABLE_NET     _IO('G', 3)

/* get the base tty number क्रम a configured gsmmux tty */
#घोषणा GSMIOC_GETFIRST		_IOR('G', 4, __u32)

#पूर्ण_अगर
