<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  Universal TUN/TAP device driver.
 *  Copyright (C) 1999-2000 Maxim Krasnyansky <max_mk@yahoo.com>
 */
#अगर_अघोषित __IF_TUN_H
#घोषणा __IF_TUN_H

#समावेश <uapi/linux/अगर_tun.h>
#समावेश <uapi/linux/virtio_net.h>

#घोषणा TUN_XDP_FLAG 0x1UL

#घोषणा TUN_MSG_UBUF 1
#घोषणा TUN_MSG_PTR  2
काष्ठा tun_msg_ctl अणु
	अचिन्हित लघु type;
	अचिन्हित लघु num;
	व्योम *ptr;
पूर्ण;

काष्ठा tun_xdp_hdr अणु
	पूर्णांक buflen;
	काष्ठा virtio_net_hdr gso;
पूर्ण;

#अगर defined(CONFIG_TUN) || defined(CONFIG_TUN_MODULE)
काष्ठा socket *tun_get_socket(काष्ठा file *);
काष्ठा ptr_ring *tun_get_tx_ring(काष्ठा file *file);
अटल अंतरभूत bool tun_is_xdp_frame(व्योम *ptr)
अणु
       वापस (अचिन्हित दीर्घ)ptr & TUN_XDP_FLAG;
पूर्ण
अटल अंतरभूत व्योम *tun_xdp_to_ptr(काष्ठा xdp_frame *xdp)
अणु
       वापस (व्योम *)((अचिन्हित दीर्घ)xdp | TUN_XDP_FLAG);
पूर्ण
अटल अंतरभूत काष्ठा xdp_frame *tun_ptr_to_xdp(व्योम *ptr)
अणु
       वापस (व्योम *)((अचिन्हित दीर्घ)ptr & ~TUN_XDP_FLAG);
पूर्ण
व्योम tun_ptr_मुक्त(व्योम *ptr);
#अन्यथा
#समावेश <linux/err.h>
#समावेश <linux/त्रुटिसं.स>
काष्ठा file;
काष्ठा socket;
अटल अंतरभूत काष्ठा socket *tun_get_socket(काष्ठा file *f)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
अटल अंतरभूत काष्ठा ptr_ring *tun_get_tx_ring(काष्ठा file *f)
अणु
	वापस ERR_PTR(-EINVAL);
पूर्ण
अटल अंतरभूत bool tun_is_xdp_frame(व्योम *ptr)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत व्योम *tun_xdp_to_ptr(काष्ठा xdp_frame *xdp)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत काष्ठा xdp_frame *tun_ptr_to_xdp(व्योम *ptr)
अणु
	वापस शून्य;
पूर्ण
अटल अंतरभूत व्योम tun_ptr_मुक्त(व्योम *ptr)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_TUN */
#पूर्ण_अगर /* __IF_TUN_H */
