<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
// Copyright (C) 2018 Facebook

#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <bpf/libbpf.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/tc_act/tc_bpf.h>

#समावेश "bpf/nlattr.h"
#समावेश "main.h"
#समावेश "netlink_dumper.h"

अटल व्योम xdp_dump_prog_id(काष्ठा nlattr **tb, पूर्णांक attr,
			     स्थिर अक्षर *mode,
			     bool new_json_object)
अणु
	अगर (!tb[attr])
		वापस;

	अगर (new_json_object)
		NET_START_OBJECT
	NET_DUMP_STR("mode", " %s", mode);
	NET_DUMP_UINT("id", " id %u", libbpf_nla_getattr_u32(tb[attr]))
	अगर (new_json_object)
		NET_END_OBJECT
पूर्ण

अटल पूर्णांक करो_xdp_dump_one(काष्ठा nlattr *attr, अचिन्हित पूर्णांक अगरindex,
			   स्थिर अक्षर *name)
अणु
	काष्ठा nlattr *tb[IFLA_XDP_MAX + 1];
	अचिन्हित अक्षर mode;

	अगर (libbpf_nla_parse_nested(tb, IFLA_XDP_MAX, attr, शून्य) < 0)
		वापस -1;

	अगर (!tb[IFLA_XDP_ATTACHED])
		वापस 0;

	mode = libbpf_nla_getattr_u8(tb[IFLA_XDP_ATTACHED]);
	अगर (mode == XDP_ATTACHED_NONE)
		वापस 0;

	NET_START_OBJECT;
	अगर (name)
		NET_DUMP_STR("devname", "%s", name);
	NET_DUMP_UINT("ifindex", "(%d)", अगरindex);

	अगर (mode == XDP_ATTACHED_MULTI) अणु
		अगर (json_output) अणु
			jsonw_name(json_wtr, "multi_attachments");
			jsonw_start_array(json_wtr);
		पूर्ण
		xdp_dump_prog_id(tb, IFLA_XDP_SKB_PROG_ID, "generic", true);
		xdp_dump_prog_id(tb, IFLA_XDP_DRV_PROG_ID, "driver", true);
		xdp_dump_prog_id(tb, IFLA_XDP_HW_PROG_ID, "offload", true);
		अगर (json_output)
			jsonw_end_array(json_wtr);
	पूर्ण अन्यथा अगर (mode == XDP_ATTACHED_DRV) अणु
		xdp_dump_prog_id(tb, IFLA_XDP_PROG_ID, "driver", false);
	पूर्ण अन्यथा अगर (mode == XDP_ATTACHED_SKB) अणु
		xdp_dump_prog_id(tb, IFLA_XDP_PROG_ID, "generic", false);
	पूर्ण अन्यथा अगर (mode == XDP_ATTACHED_HW) अणु
		xdp_dump_prog_id(tb, IFLA_XDP_PROG_ID, "offload", false);
	पूर्ण

	NET_END_OBJECT_FINAL;
	वापस 0;
पूर्ण

पूर्णांक करो_xdp_dump(काष्ठा अगरinfomsg *अगरinfo, काष्ठा nlattr **tb)
अणु
	अगर (!tb[IFLA_XDP])
		वापस 0;

	वापस करो_xdp_dump_one(tb[IFLA_XDP], अगरinfo->अगरi_index,
			       libbpf_nla_getattr_str(tb[IFLA_IFNAME]));
पूर्ण

अटल पूर्णांक करो_bpf_dump_one_act(काष्ठा nlattr *attr)
अणु
	काष्ठा nlattr *tb[TCA_ACT_BPF_MAX + 1];

	अगर (libbpf_nla_parse_nested(tb, TCA_ACT_BPF_MAX, attr, शून्य) < 0)
		वापस -LIBBPF_ERRNO__NLPARSE;

	अगर (!tb[TCA_ACT_BPF_PARMS])
		वापस -LIBBPF_ERRNO__NLPARSE;

	NET_START_OBJECT_NESTED2;
	अगर (tb[TCA_ACT_BPF_NAME])
		NET_DUMP_STR("name", "%s",
			     libbpf_nla_getattr_str(tb[TCA_ACT_BPF_NAME]));
	अगर (tb[TCA_ACT_BPF_ID])
		NET_DUMP_UINT("id", " id %u",
			      libbpf_nla_getattr_u32(tb[TCA_ACT_BPF_ID]));
	NET_END_OBJECT_NESTED;
	वापस 0;
पूर्ण

अटल पूर्णांक करो_dump_one_act(काष्ठा nlattr *attr)
अणु
	काष्ठा nlattr *tb[TCA_ACT_MAX + 1];

	अगर (!attr)
		वापस 0;

	अगर (libbpf_nla_parse_nested(tb, TCA_ACT_MAX, attr, शून्य) < 0)
		वापस -LIBBPF_ERRNO__NLPARSE;

	अगर (tb[TCA_ACT_KIND] &&
	    म_भेद(libbpf_nla_data(tb[TCA_ACT_KIND]), "bpf") == 0)
		वापस करो_bpf_dump_one_act(tb[TCA_ACT_OPTIONS]);

	वापस 0;
पूर्ण

अटल पूर्णांक करो_bpf_act_dump(काष्ठा nlattr *attr)
अणु
	काष्ठा nlattr *tb[TCA_ACT_MAX_PRIO + 1];
	पूर्णांक act, ret;

	अगर (libbpf_nla_parse_nested(tb, TCA_ACT_MAX_PRIO, attr, शून्य) < 0)
		वापस -LIBBPF_ERRNO__NLPARSE;

	NET_START_ARRAY("act", " %s [");
	क्रम (act = 0; act <= TCA_ACT_MAX_PRIO; act++) अणु
		ret = करो_dump_one_act(tb[act]);
		अगर (ret)
			अवरोध;
	पूर्ण
	NET_END_ARRAY("] ");

	वापस ret;
पूर्ण

अटल पूर्णांक करो_bpf_filter_dump(काष्ठा nlattr *attr)
अणु
	काष्ठा nlattr *tb[TCA_BPF_MAX + 1];
	पूर्णांक ret;

	अगर (libbpf_nla_parse_nested(tb, TCA_BPF_MAX, attr, शून्य) < 0)
		वापस -LIBBPF_ERRNO__NLPARSE;

	अगर (tb[TCA_BPF_NAME])
		NET_DUMP_STR("name", " %s",
			     libbpf_nla_getattr_str(tb[TCA_BPF_NAME]));
	अगर (tb[TCA_BPF_ID])
		NET_DUMP_UINT("id", " id %u",
			      libbpf_nla_getattr_u32(tb[TCA_BPF_ID]));
	अगर (tb[TCA_BPF_ACT]) अणु
		ret = करो_bpf_act_dump(tb[TCA_BPF_ACT]);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक करो_filter_dump(काष्ठा tcmsg *info, काष्ठा nlattr **tb, स्थिर अक्षर *kind,
		   स्थिर अक्षर *devname, पूर्णांक अगरindex)
अणु
	पूर्णांक ret = 0;

	अगर (tb[TCA_OPTIONS] &&
	    म_भेद(libbpf_nla_data(tb[TCA_KIND]), "bpf") == 0) अणु
		NET_START_OBJECT;
		अगर (devname[0] != '\0')
			NET_DUMP_STR("devname", "%s", devname);
		NET_DUMP_UINT("ifindex", "(%u)", अगरindex);
		NET_DUMP_STR("kind", " %s", kind);
		ret = करो_bpf_filter_dump(tb[TCA_OPTIONS]);
		NET_END_OBJECT_FINAL;
	पूर्ण

	वापस ret;
पूर्ण
