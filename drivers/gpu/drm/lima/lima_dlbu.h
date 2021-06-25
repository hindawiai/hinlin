<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/* Copyright 2018-2019 Qiang Yu <yuq825@gmail.com> */

#अगर_अघोषित __LIMA_DLBU_H__
#घोषणा __LIMA_DLBU_H__

काष्ठा lima_ip;
काष्ठा lima_device;

व्योम lima_dlbu_enable(काष्ठा lima_device *dev, पूर्णांक num_pp);
व्योम lima_dlbu_disable(काष्ठा lima_device *dev);

व्योम lima_dlbu_set_reg(काष्ठा lima_ip *ip, u32 *reg);

पूर्णांक lima_dlbu_resume(काष्ठा lima_ip *ip);
व्योम lima_dlbu_suspend(काष्ठा lima_ip *ip);
पूर्णांक lima_dlbu_init(काष्ठा lima_ip *ip);
व्योम lima_dlbu_fini(काष्ठा lima_ip *ip);

#पूर्ण_अगर
