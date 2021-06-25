<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2017 Facebook
 */
#अगर_अघोषित __MAP_IN_MAP_H__
#घोषणा __MAP_IN_MAP_H__

#समावेश <linux/types.h>

काष्ठा file;
काष्ठा bpf_map;

काष्ठा bpf_map *bpf_map_meta_alloc(पूर्णांक inner_map_ufd);
व्योम bpf_map_meta_मुक्त(काष्ठा bpf_map *map_meta);
व्योम *bpf_map_fd_get_ptr(काष्ठा bpf_map *map, काष्ठा file *map_file,
			 पूर्णांक ufd);
व्योम bpf_map_fd_put_ptr(व्योम *ptr);
u32 bpf_map_fd_sys_lookup_elem(व्योम *ptr);

#पूर्ण_अगर
