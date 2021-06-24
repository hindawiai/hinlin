<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR MIT */
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#अगर_अघोषित __LIMA_PP_H__
#घोषणा __LIMA_PP_H__

काष्ठा lima_ip;
काष्ठा lima_device;

पूर्णांक lima_pp_resume(काष्ठा lima_ip *ip);
व्योम lima_pp_suspend(काष्ठा lima_ip *ip);
पूर्णांक lima_pp_init(काष्ठा lima_ip *ip);
व्योम lima_pp_fini(काष्ठा lima_ip *ip);

पूर्णांक lima_pp_bcast_resume(काष्ठा lima_ip *ip);
व्योम lima_pp_bcast_suspend(काष्ठा lima_ip *ip);
पूर्णांक lima_pp_bcast_init(काष्ठा lima_ip *ip);
व्योम lima_pp_bcast_fini(काष्ठा lima_ip *ip);

पूर्णांक lima_pp_pipe_init(काष्ठा lima_device *dev);
व्योम lima_pp_pipe_fini(काष्ठा lima_device *dev);

#पूर्ण_अगर
