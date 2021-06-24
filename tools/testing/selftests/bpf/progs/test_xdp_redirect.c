<शैली गुरु>
/* Copyright (c) 2017 VMware
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License क्रम more details.
 */
#समावेश <linux/bpf.h>
#समावेश <bpf/bpf_helpers.h>

पूर्णांक _version SEC("version") = 1;

SEC("redirect_to_111")
पूर्णांक xdp_redirect_to_111(काष्ठा xdp_md *xdp)
अणु
	वापस bpf_redirect(111, 0);
पूर्ण
SEC("redirect_to_222")
पूर्णांक xdp_redirect_to_222(काष्ठा xdp_md *xdp)
अणु
	वापस bpf_redirect(222, 0);
पूर्ण

अक्षर _license[] SEC("license") = "GPL";
