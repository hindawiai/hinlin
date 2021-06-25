<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2017-2018 Netronome Systems, Inc. */

#घोषणा _GNU_SOURCE
#समावेश <प्रकार.स>
#समावेश <त्रुटिसं.स>
#समावेश <fcntl.h>
#समावेश <ftw.h>
#समावेश <libgen.h>
#समावेश <mntent.h>
#समावेश <stdbool.h>
#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <linux/सीमा.स>
#समावेश <linux/magic.h>
#समावेश <net/अगर.h>
#समावेश <sys/mount.h>
#समावेश <sys/resource.h>
#समावेश <sys/स्थिति.स>
#समावेश <sys/vfs.h>

#समावेश <bpf/bpf.h>
#समावेश <bpf/libbpf.h> /* libbpf_num_possible_cpus */

#समावेश "main.h"

#अगर_अघोषित BPF_FS_MAGIC
#घोषणा BPF_FS_MAGIC		0xcafe4a11
#पूर्ण_अगर

स्थिर अक्षर * स्थिर attach_type_name[__MAX_BPF_ATTACH_TYPE] = अणु
	[BPF_CGROUP_INET_INGRESS]	= "ingress",
	[BPF_CGROUP_INET_EGRESS]	= "egress",
	[BPF_CGROUP_INET_SOCK_CREATE]	= "sock_create",
	[BPF_CGROUP_INET_SOCK_RELEASE]	= "sock_release",
	[BPF_CGROUP_SOCK_OPS]		= "sock_ops",
	[BPF_CGROUP_DEVICE]		= "device",
	[BPF_CGROUP_INET4_BIND]		= "bind4",
	[BPF_CGROUP_INET6_BIND]		= "bind6",
	[BPF_CGROUP_INET4_CONNECT]	= "connect4",
	[BPF_CGROUP_INET6_CONNECT]	= "connect6",
	[BPF_CGROUP_INET4_POST_BIND]	= "post_bind4",
	[BPF_CGROUP_INET6_POST_BIND]	= "post_bind6",
	[BPF_CGROUP_INET4_GETPEERNAME]	= "getpeername4",
	[BPF_CGROUP_INET6_GETPEERNAME]	= "getpeername6",
	[BPF_CGROUP_INET4_GETSOCKNAME]	= "getsockname4",
	[BPF_CGROUP_INET6_GETSOCKNAME]	= "getsockname6",
	[BPF_CGROUP_UDP4_SENDMSG]	= "sendmsg4",
	[BPF_CGROUP_UDP6_SENDMSG]	= "sendmsg6",
	[BPF_CGROUP_SYSCTL]		= "sysctl",
	[BPF_CGROUP_UDP4_RECVMSG]	= "recvmsg4",
	[BPF_CGROUP_UDP6_RECVMSG]	= "recvmsg6",
	[BPF_CGROUP_GETSOCKOPT]		= "getsockopt",
	[BPF_CGROUP_SETSOCKOPT]		= "setsockopt",

	[BPF_SK_SKB_STREAM_PARSER]	= "sk_skb_stream_parser",
	[BPF_SK_SKB_STREAM_VERDICT]	= "sk_skb_stream_verdict",
	[BPF_SK_SKB_VERDICT]		= "sk_skb_verdict",
	[BPF_SK_MSG_VERDICT]		= "sk_msg_verdict",
	[BPF_LIRC_MODE2]		= "lirc_mode2",
	[BPF_FLOW_DISSECTOR]		= "flow_dissector",
	[BPF_TRACE_RAW_TP]		= "raw_tp",
	[BPF_TRACE_FENTRY]		= "fentry",
	[BPF_TRACE_FEXIT]		= "fexit",
	[BPF_MODIFY_RETURN]		= "mod_ret",
	[BPF_LSM_MAC]			= "lsm_mac",
	[BPF_SK_LOOKUP]			= "sk_lookup",
पूर्ण;

व्योम p_err(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	बहु_शुरू(ap, fmt);
	अगर (json_output) अणु
		jsonw_start_object(json_wtr);
		jsonw_name(json_wtr, "error");
		jsonw_भ_लिखो_enquote(json_wtr, fmt, ap);
		jsonw_end_object(json_wtr);
	पूर्ण अन्यथा अणु
		ख_लिखो(मानक_त्रुटि, "Error: ");
		भख_लिखो(मानक_त्रुटि, fmt, ap);
		ख_लिखो(मानक_त्रुटि, "\n");
	पूर्ण
	बहु_पूर्ण(ap);
पूर्ण

व्योम p_info(स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची ap;

	अगर (json_output)
		वापस;

	बहु_शुरू(ap, fmt);
	भख_लिखो(मानक_त्रुटि, fmt, ap);
	ख_लिखो(मानक_त्रुटि, "\n");
	बहु_पूर्ण(ap);
पूर्ण

अटल bool is_bpffs(अक्षर *path)
अणु
	काष्ठा statfs st_fs;

	अगर (statfs(path, &st_fs) < 0)
		वापस false;

	वापस (अचिन्हित दीर्घ)st_fs.f_type == BPF_FS_MAGIC;
पूर्ण

व्योम set_max_rlimit(व्योम)
अणु
	काष्ठा rlimit rinf = अणु RLIM_अनन्त, RLIM_अनन्त पूर्ण;

	setrlimit(RLIMIT_MEMLOCK, &rinf);
पूर्ण

अटल पूर्णांक
mnt_fs(स्थिर अक्षर *target, स्थिर अक्षर *type, अक्षर *buff, माप_प्रकार bufflen)
अणु
	bool bind_करोne = false;

	जबतक (mount("", target, "none", MS_PRIVATE | MS_REC, शून्य)) अणु
		अगर (त्रुटि_सं != EINVAL || bind_करोne) अणु
			snम_लिखो(buff, bufflen,
				 "mount --make-private %s failed: %s",
				 target, म_त्रुटि(त्रुटि_सं));
			वापस -1;
		पूर्ण

		अगर (mount(target, target, "none", MS_BIND, शून्य)) अणु
			snम_लिखो(buff, bufflen,
				 "mount --bind %s %s failed: %s",
				 target, target, म_त्रुटि(त्रुटि_सं));
			वापस -1;
		पूर्ण

		bind_करोne = true;
	पूर्ण

	अगर (mount(type, target, type, 0, "mode=0700")) अणु
		snम_लिखो(buff, bufflen, "mount -t %s %s %s failed: %s",
			 type, type, target, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mount_tracefs(स्थिर अक्षर *target)
अणु
	अक्षर err_str[ERR_MAX_LEN];
	पूर्णांक err;

	err = mnt_fs(target, "tracefs", err_str, ERR_MAX_LEN);
	अगर (err) अणु
		err_str[ERR_MAX_LEN - 1] = '\0';
		p_err("can't mount tracefs: %s", err_str);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक खोलो_obj_pinned(स्थिर अक्षर *path, bool quiet)
अणु
	अक्षर *pname;
	पूर्णांक fd = -1;

	pname = strdup(path);
	अगर (!pname) अणु
		अगर (!quiet)
			p_err("mem alloc failed");
		जाओ out_ret;
	पूर्ण

	fd = bpf_obj_get(pname);
	अगर (fd < 0) अणु
		अगर (!quiet)
			p_err("bpf obj get (%s): %s", pname,
			      त्रुटि_सं == EACCES && !is_bpffs(स_नाम(pname)) ?
			    "directory not in bpf file system (bpffs)" :
			    म_त्रुटि(त्रुटि_सं));
		जाओ out_मुक्त;
	पूर्ण

out_मुक्त:
	मुक्त(pname);
out_ret:
	वापस fd;
पूर्ण

पूर्णांक खोलो_obj_pinned_any(स्थिर अक्षर *path, क्रमागत bpf_obj_type exp_type)
अणु
	क्रमागत bpf_obj_type type;
	पूर्णांक fd;

	fd = खोलो_obj_pinned(path, false);
	अगर (fd < 0)
		वापस -1;

	type = get_fd_type(fd);
	अगर (type < 0) अणु
		बंद(fd);
		वापस type;
	पूर्ण
	अगर (type != exp_type) अणु
		p_err("incorrect object type: %s", get_fd_type_name(type));
		बंद(fd);
		वापस -1;
	पूर्ण

	वापस fd;
पूर्ण

पूर्णांक mount_bpffs_क्रम_pin(स्थिर अक्षर *name)
अणु
	अक्षर err_str[ERR_MAX_LEN];
	अक्षर *file;
	अक्षर *dir;
	पूर्णांक err = 0;

	file = दो_स्मृति(म_माप(name) + 1);
	म_नकल(file, name);
	dir = स_नाम(file);

	अगर (is_bpffs(dir))
		/* nothing to करो अगर alपढ़ोy mounted */
		जाओ out_मुक्त;

	अगर (block_mount) अणु
		p_err("no BPF file system found, not mounting it due to --nomount option");
		err = -1;
		जाओ out_मुक्त;
	पूर्ण

	err = mnt_fs(dir, "bpf", err_str, ERR_MAX_LEN);
	अगर (err) अणु
		err_str[ERR_MAX_LEN - 1] = '\0';
		p_err("can't mount BPF file system to pin the object (%s): %s",
		      name, err_str);
	पूर्ण

out_मुक्त:
	मुक्त(file);
	वापस err;
पूर्ण

पूर्णांक करो_pin_fd(पूर्णांक fd, स्थिर अक्षर *name)
अणु
	पूर्णांक err;

	err = mount_bpffs_क्रम_pin(name);
	अगर (err)
		वापस err;

	err = bpf_obj_pin(fd, name);
	अगर (err)
		p_err("can't pin the object (%s): %s", name, म_त्रुटि(त्रुटि_सं));

	वापस err;
पूर्ण

पूर्णांक करो_pin_any(पूर्णांक argc, अक्षर **argv, पूर्णांक (*get_fd)(पूर्णांक *, अक्षर ***))
अणु
	पूर्णांक err;
	पूर्णांक fd;

	fd = get_fd(&argc, &argv);
	अगर (fd < 0)
		वापस fd;

	err = करो_pin_fd(fd, *argv);

	बंद(fd);
	वापस err;
पूर्ण

स्थिर अक्षर *get_fd_type_name(क्रमागत bpf_obj_type type)
अणु
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		[BPF_OBJ_UNKNOWN]	= "unknown",
		[BPF_OBJ_PROG]		= "prog",
		[BPF_OBJ_MAP]		= "map",
	पूर्ण;

	अगर (type < 0 || type >= ARRAY_SIZE(names) || !names[type])
		वापस names[BPF_OBJ_UNKNOWN];

	वापस names[type];
पूर्ण

पूर्णांक get_fd_type(पूर्णांक fd)
अणु
	अक्षर path[PATH_MAX];
	अक्षर buf[512];
	sमाप_प्रकार n;

	snम_लिखो(path, माप(path), "/proc/self/fd/%d", fd);

	n = पढ़ोlink(path, buf, माप(buf));
	अगर (n < 0) अणु
		p_err("can't read link type: %s", म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण
	अगर (n == माप(path)) अणु
		p_err("can't read link type: path too long!");
		वापस -1;
	पूर्ण

	अगर (म_माला(buf, "bpf-map"))
		वापस BPF_OBJ_MAP;
	अन्यथा अगर (म_माला(buf, "bpf-prog"))
		वापस BPF_OBJ_PROG;
	अन्यथा अगर (म_माला(buf, "bpf-link"))
		वापस BPF_OBJ_LINK;

	वापस BPF_OBJ_UNKNOWN;
पूर्ण

अक्षर *get_fdinfo(पूर्णांक fd, स्थिर अक्षर *key)
अणु
	अक्षर path[PATH_MAX];
	अक्षर *line = शून्य;
	माप_प्रकार line_n = 0;
	sमाप_प्रकार n;
	खाता *fdi;

	snम_लिखो(path, माप(path), "/proc/self/fdinfo/%d", fd);

	fdi = ख_खोलो(path, "r");
	अगर (!fdi)
		वापस शून्य;

	जबतक ((n = getline(&line, &line_n, fdi)) > 0) अणु
		अक्षर *value;
		पूर्णांक len;

		अगर (!म_माला(line, key))
			जारी;

		ख_बंद(fdi);

		value = म_अक्षर(line, '\t');
		अगर (!value || !value[1]) अणु
			मुक्त(line);
			वापस शून्य;
		पूर्ण
		value++;

		len = म_माप(value);
		स_हटाओ(line, value, len);
		line[len - 1] = '\0';

		वापस line;
	पूर्ण

	मुक्त(line);
	ख_बंद(fdi);
	वापस शून्य;
पूर्ण

व्योम prपूर्णांक_data_json(uपूर्णांक8_t *data, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक i;

	jsonw_start_array(json_wtr);
	क्रम (i = 0; i < len; i++)
		jsonw_म_लिखो(json_wtr, "%d", data[i]);
	jsonw_end_array(json_wtr);
पूर्ण

व्योम prपूर्णांक_hex_data_json(uपूर्णांक8_t *data, माप_प्रकार len)
अणु
	अचिन्हित पूर्णांक i;

	jsonw_start_array(json_wtr);
	क्रम (i = 0; i < len; i++)
		jsonw_म_लिखो(json_wtr, "\"0x%02hhx\"", data[i]);
	jsonw_end_array(json_wtr);
पूर्ण

/* extra params क्रम nftw cb */
अटल काष्ठा pinned_obj_table *build_fn_table;
अटल क्रमागत bpf_obj_type build_fn_type;

अटल पूर्णांक करो_build_table_cb(स्थिर अक्षर *fpath, स्थिर काष्ठा stat *sb,
			     पूर्णांक typeflag, काष्ठा FTW *ftwbuf)
अणु
	काष्ठा bpf_prog_info pinned_info;
	__u32 len = माप(pinned_info);
	काष्ठा pinned_obj *obj_node;
	क्रमागत bpf_obj_type objtype;
	पूर्णांक fd, err = 0;

	अगर (typeflag != FTW_F)
		जाओ out_ret;

	fd = खोलो_obj_pinned(fpath, true);
	अगर (fd < 0)
		जाओ out_ret;

	objtype = get_fd_type(fd);
	अगर (objtype != build_fn_type)
		जाओ out_बंद;

	स_रखो(&pinned_info, 0, माप(pinned_info));
	अगर (bpf_obj_get_info_by_fd(fd, &pinned_info, &len))
		जाओ out_बंद;

	obj_node = सुस्मृति(1, माप(*obj_node));
	अगर (!obj_node) अणु
		err = -1;
		जाओ out_बंद;
	पूर्ण

	obj_node->id = pinned_info.id;
	obj_node->path = strdup(fpath);
	अगर (!obj_node->path) अणु
		err = -1;
		मुक्त(obj_node);
		जाओ out_बंद;
	पूर्ण

	hash_add(build_fn_table->table, &obj_node->hash, obj_node->id);
out_बंद:
	बंद(fd);
out_ret:
	वापस err;
पूर्ण

पूर्णांक build_pinned_obj_table(काष्ठा pinned_obj_table *tab,
			   क्रमागत bpf_obj_type type)
अणु
	काष्ठा mntent *mntent = शून्य;
	खाता *mntfile = शून्य;
	पूर्णांक flags = FTW_PHYS;
	पूर्णांक nखोलोfd = 16;
	पूर्णांक err = 0;

	mntfile = seपंचांगntent("/proc/mounts", "r");
	अगर (!mntfile)
		वापस -1;

	build_fn_table = tab;
	build_fn_type = type;

	जबतक ((mntent = geपंचांगntent(mntfile))) अणु
		अक्षर *path = mntent->mnt_dir;

		अगर (म_भेदन(mntent->mnt_type, "bpf", 3) != 0)
			जारी;
		err = nftw(path, करो_build_table_cb, nखोलोfd, flags);
		अगर (err)
			अवरोध;
	पूर्ण
	ख_बंद(mntfile);
	वापस err;
पूर्ण

व्योम delete_pinned_obj_table(काष्ठा pinned_obj_table *tab)
अणु
	काष्ठा pinned_obj *obj;
	काष्ठा hlist_node *पंचांगp;
	अचिन्हित पूर्णांक bkt;

	hash_क्रम_each_safe(tab->table, bkt, पंचांगp, obj, hash) अणु
		hash_del(&obj->hash);
		मुक्त(obj->path);
		मुक्त(obj);
	पूर्ण
पूर्ण

अचिन्हित पूर्णांक get_page_size(व्योम)
अणु
	अटल पूर्णांक result;

	अगर (!result)
		result = getpagesize();
	वापस result;
पूर्ण

अचिन्हित पूर्णांक get_possible_cpus(व्योम)
अणु
	पूर्णांक cpus = libbpf_num_possible_cpus();

	अगर (cpus < 0) अणु
		p_err("Can't get # of possible cpus: %s", म_त्रुटि(-cpus));
		निकास(-1);
	पूर्ण
	वापस cpus;
पूर्ण

अटल अक्षर *
अगरindex_to_name_ns(__u32 अगरindex, __u32 ns_dev, __u32 ns_ino, अक्षर *buf)
अणु
	काष्ठा stat st;
	पूर्णांक err;

	err = stat("/proc/self/ns/net", &st);
	अगर (err) अणु
		p_err("Can't stat /proc/self: %s", म_त्रुटि(त्रुटि_सं));
		वापस शून्य;
	पूर्ण

	अगर (st.st_dev != ns_dev || st.st_ino != ns_ino)
		वापस शून्य;

	वापस अगर_indextoname(अगरindex, buf);
पूर्ण

अटल पूर्णांक पढ़ो_sysfs_hex_पूर्णांक(अक्षर *path)
अणु
	अक्षर venकरोr_id_buf[8];
	पूर्णांक len;
	पूर्णांक fd;

	fd = खोलो(path, O_RDONLY);
	अगर (fd < 0) अणु
		p_err("Can't open %s: %s", path, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण

	len = पढ़ो(fd, venकरोr_id_buf, माप(venकरोr_id_buf));
	बंद(fd);
	अगर (len < 0) अणु
		p_err("Can't read %s: %s", path, म_त्रुटि(त्रुटि_सं));
		वापस -1;
	पूर्ण
	अगर (len >= (पूर्णांक)माप(venकरोr_id_buf)) अणु
		p_err("Value in %s too long", path);
		वापस -1;
	पूर्ण

	venकरोr_id_buf[len] = 0;

	वापस म_से_दीर्घ(venकरोr_id_buf, शून्य, 0);
पूर्ण

अटल पूर्णांक पढ़ो_sysfs_netdev_hex_पूर्णांक(अक्षर *devname, स्थिर अक्षर *entry_name)
अणु
	अक्षर full_path[64];

	snम_लिखो(full_path, माप(full_path), "/sys/class/net/%s/device/%s",
		 devname, entry_name);

	वापस पढ़ो_sysfs_hex_पूर्णांक(full_path);
पूर्ण

स्थिर अक्षर *
अगरindex_to_bfd_params(__u32 अगरindex, __u64 ns_dev, __u64 ns_ino,
		      स्थिर अक्षर **opt)
अणु
	अक्षर devname[IF_NAMESIZE];
	पूर्णांक venकरोr_id;
	पूर्णांक device_id;

	अगर (!अगरindex_to_name_ns(अगरindex, ns_dev, ns_ino, devname)) अणु
		p_err("Can't get net device name for ifindex %d: %s", अगरindex,
		      म_त्रुटि(त्रुटि_सं));
		वापस शून्य;
	पूर्ण

	venकरोr_id = पढ़ो_sysfs_netdev_hex_पूर्णांक(devname, "vendor");
	अगर (venकरोr_id < 0) अणु
		p_err("Can't get device vendor id for %s", devname);
		वापस शून्य;
	पूर्ण

	चयन (venकरोr_id) अणु
	हाल 0x19ee:
		device_id = पढ़ो_sysfs_netdev_hex_पूर्णांक(devname, "device");
		अगर (device_id != 0x4000 &&
		    device_id != 0x6000 &&
		    device_id != 0x6003)
			p_info("Unknown NFP device ID, assuming it is NFP-6xxx arch");
		*opt = "ctx4";
		वापस "NFP-6xxx";
	शेष:
		p_err("Can't get bfd arch name for device vendor id 0x%04x",
		      venकरोr_id);
		वापस शून्य;
	पूर्ण
पूर्ण

व्योम prपूर्णांक_dev_plain(__u32 अगरindex, __u64 ns_dev, __u64 ns_inode)
अणु
	अक्षर name[IF_NAMESIZE];

	अगर (!अगरindex)
		वापस;

	म_लिखो("  offloaded_to ");
	अगर (अगरindex_to_name_ns(अगरindex, ns_dev, ns_inode, name))
		म_लिखो("%s", name);
	अन्यथा
		म_लिखो("ifindex %u ns_dev %llu ns_ino %llu",
		       अगरindex, ns_dev, ns_inode);
पूर्ण

व्योम prपूर्णांक_dev_json(__u32 अगरindex, __u64 ns_dev, __u64 ns_inode)
अणु
	अक्षर name[IF_NAMESIZE];

	अगर (!अगरindex)
		वापस;

	jsonw_name(json_wtr, "dev");
	jsonw_start_object(json_wtr);
	jsonw_uपूर्णांक_field(json_wtr, "ifindex", अगरindex);
	jsonw_uपूर्णांक_field(json_wtr, "ns_dev", ns_dev);
	jsonw_uपूर्णांक_field(json_wtr, "ns_inode", ns_inode);
	अगर (अगरindex_to_name_ns(अगरindex, ns_dev, ns_inode, name))
		jsonw_string_field(json_wtr, "ifname", name);
	jsonw_end_object(json_wtr);
पूर्ण

पूर्णांक parse_u32_arg(पूर्णांक *argc, अक्षर ***argv, __u32 *val, स्थिर अक्षर *what)
अणु
	अक्षर *endptr;

	NEXT_ARGP();

	अगर (*val) अणु
		p_err("%s already specified", what);
		वापस -1;
	पूर्ण

	*val = म_से_अदीर्घ(**argv, &endptr, 0);
	अगर (*endptr) अणु
		p_err("can't parse %s as %s", **argv, what);
		वापस -1;
	पूर्ण
	NEXT_ARGP();

	वापस 0;
पूर्ण

पूर्णांक __म_लिखो(2, 0)
prपूर्णांक_all_levels(__maybe_unused क्रमागत libbpf_prपूर्णांक_level level,
		 स्थिर अक्षर *क्रमmat, बहु_सूची args)
अणु
	वापस भख_लिखो(मानक_त्रुटि, क्रमmat, args);
पूर्ण

अटल पूर्णांक prog_fd_by_nametag(व्योम *nametag, पूर्णांक **fds, bool tag)
अणु
	अचिन्हित पूर्णांक id = 0;
	पूर्णांक fd, nb_fds = 0;
	व्योम *पंचांगp;
	पूर्णांक err;

	जबतक (true) अणु
		काष्ठा bpf_prog_info info = अणुपूर्ण;
		__u32 len = माप(info);

		err = bpf_prog_get_next_id(id, &id);
		अगर (err) अणु
			अगर (त्रुटि_सं != ENOENT) अणु
				p_err("%s", म_त्रुटि(त्रुटि_सं));
				जाओ err_बंद_fds;
			पूर्ण
			वापस nb_fds;
		पूर्ण

		fd = bpf_prog_get_fd_by_id(id);
		अगर (fd < 0) अणु
			p_err("can't get prog by id (%u): %s",
			      id, म_त्रुटि(त्रुटि_सं));
			जाओ err_बंद_fds;
		पूर्ण

		err = bpf_obj_get_info_by_fd(fd, &info, &len);
		अगर (err) अणु
			p_err("can't get prog info (%u): %s",
			      id, म_त्रुटि(त्रुटि_सं));
			जाओ err_बंद_fd;
		पूर्ण

		अगर ((tag && स_भेद(nametag, info.tag, BPF_TAG_SIZE)) ||
		    (!tag && म_भेदन(nametag, info.name, BPF_OBJ_NAME_LEN))) अणु
			बंद(fd);
			जारी;
		पूर्ण

		अगर (nb_fds > 0) अणु
			पंचांगp = पुनः_स्मृति(*fds, (nb_fds + 1) * माप(पूर्णांक));
			अगर (!पंचांगp) अणु
				p_err("failed to realloc");
				जाओ err_बंद_fd;
			पूर्ण
			*fds = पंचांगp;
		पूर्ण
		(*fds)[nb_fds++] = fd;
	पूर्ण

err_बंद_fd:
	बंद(fd);
err_बंद_fds:
	जबतक (--nb_fds >= 0)
		बंद((*fds)[nb_fds]);
	वापस -1;
पूर्ण

पूर्णांक prog_parse_fds(पूर्णांक *argc, अक्षर ***argv, पूर्णांक **fds)
अणु
	अगर (is_prefix(**argv, "id")) अणु
		अचिन्हित पूर्णांक id;
		अक्षर *endptr;

		NEXT_ARGP();

		id = म_से_अदीर्घ(**argv, &endptr, 0);
		अगर (*endptr) अणु
			p_err("can't parse %s as ID", **argv);
			वापस -1;
		पूर्ण
		NEXT_ARGP();

		(*fds)[0] = bpf_prog_get_fd_by_id(id);
		अगर ((*fds)[0] < 0) अणु
			p_err("get by id (%u): %s", id, म_त्रुटि(त्रुटि_सं));
			वापस -1;
		पूर्ण
		वापस 1;
	पूर्ण अन्यथा अगर (is_prefix(**argv, "tag")) अणु
		अचिन्हित अक्षर tag[BPF_TAG_SIZE];

		NEXT_ARGP();

		अगर (माला_पूछो(**argv, BPF_TAG_FMT, tag, tag + 1, tag + 2,
			   tag + 3, tag + 4, tag + 5, tag + 6, tag + 7)
		    != BPF_TAG_SIZE) अणु
			p_err("can't parse tag");
			वापस -1;
		पूर्ण
		NEXT_ARGP();

		वापस prog_fd_by_nametag(tag, fds, true);
	पूर्ण अन्यथा अगर (is_prefix(**argv, "name")) अणु
		अक्षर *name;

		NEXT_ARGP();

		name = **argv;
		अगर (म_माप(name) > BPF_OBJ_NAME_LEN - 1) अणु
			p_err("can't parse name");
			वापस -1;
		पूर्ण
		NEXT_ARGP();

		वापस prog_fd_by_nametag(name, fds, false);
	पूर्ण अन्यथा अगर (is_prefix(**argv, "pinned")) अणु
		अक्षर *path;

		NEXT_ARGP();

		path = **argv;
		NEXT_ARGP();

		(*fds)[0] = खोलो_obj_pinned_any(path, BPF_OBJ_PROG);
		अगर ((*fds)[0] < 0)
			वापस -1;
		वापस 1;
	पूर्ण

	p_err("expected 'id', 'tag', 'name' or 'pinned', got: '%s'?", **argv);
	वापस -1;
पूर्ण

पूर्णांक prog_parse_fd(पूर्णांक *argc, अक्षर ***argv)
अणु
	पूर्णांक *fds = शून्य;
	पूर्णांक nb_fds, fd;

	fds = दो_स्मृति(माप(पूर्णांक));
	अगर (!fds) अणु
		p_err("mem alloc failed");
		वापस -1;
	पूर्ण
	nb_fds = prog_parse_fds(argc, argv, &fds);
	अगर (nb_fds != 1) अणु
		अगर (nb_fds > 1) अणु
			p_err("several programs match this handle");
			जबतक (nb_fds--)
				बंद(fds[nb_fds]);
		पूर्ण
		fd = -1;
		जाओ निकास_मुक्त;
	पूर्ण

	fd = fds[0];
निकास_मुक्त:
	मुक्त(fds);
	वापस fd;
पूर्ण

अटल पूर्णांक map_fd_by_name(अक्षर *name, पूर्णांक **fds)
अणु
	अचिन्हित पूर्णांक id = 0;
	पूर्णांक fd, nb_fds = 0;
	व्योम *पंचांगp;
	पूर्णांक err;

	जबतक (true) अणु
		काष्ठा bpf_map_info info = अणुपूर्ण;
		__u32 len = माप(info);

		err = bpf_map_get_next_id(id, &id);
		अगर (err) अणु
			अगर (त्रुटि_सं != ENOENT) अणु
				p_err("%s", म_त्रुटि(त्रुटि_सं));
				जाओ err_बंद_fds;
			पूर्ण
			वापस nb_fds;
		पूर्ण

		fd = bpf_map_get_fd_by_id(id);
		अगर (fd < 0) अणु
			p_err("can't get map by id (%u): %s",
			      id, म_त्रुटि(त्रुटि_सं));
			जाओ err_बंद_fds;
		पूर्ण

		err = bpf_obj_get_info_by_fd(fd, &info, &len);
		अगर (err) अणु
			p_err("can't get map info (%u): %s",
			      id, म_त्रुटि(त्रुटि_सं));
			जाओ err_बंद_fd;
		पूर्ण

		अगर (म_भेदन(name, info.name, BPF_OBJ_NAME_LEN)) अणु
			बंद(fd);
			जारी;
		पूर्ण

		अगर (nb_fds > 0) अणु
			पंचांगp = पुनः_स्मृति(*fds, (nb_fds + 1) * माप(पूर्णांक));
			अगर (!पंचांगp) अणु
				p_err("failed to realloc");
				जाओ err_बंद_fd;
			पूर्ण
			*fds = पंचांगp;
		पूर्ण
		(*fds)[nb_fds++] = fd;
	पूर्ण

err_बंद_fd:
	बंद(fd);
err_बंद_fds:
	जबतक (--nb_fds >= 0)
		बंद((*fds)[nb_fds]);
	वापस -1;
पूर्ण

पूर्णांक map_parse_fds(पूर्णांक *argc, अक्षर ***argv, पूर्णांक **fds)
अणु
	अगर (is_prefix(**argv, "id")) अणु
		अचिन्हित पूर्णांक id;
		अक्षर *endptr;

		NEXT_ARGP();

		id = म_से_अदीर्घ(**argv, &endptr, 0);
		अगर (*endptr) अणु
			p_err("can't parse %s as ID", **argv);
			वापस -1;
		पूर्ण
		NEXT_ARGP();

		(*fds)[0] = bpf_map_get_fd_by_id(id);
		अगर ((*fds)[0] < 0) अणु
			p_err("get map by id (%u): %s", id, म_त्रुटि(त्रुटि_सं));
			वापस -1;
		पूर्ण
		वापस 1;
	पूर्ण अन्यथा अगर (is_prefix(**argv, "name")) अणु
		अक्षर *name;

		NEXT_ARGP();

		name = **argv;
		अगर (म_माप(name) > BPF_OBJ_NAME_LEN - 1) अणु
			p_err("can't parse name");
			वापस -1;
		पूर्ण
		NEXT_ARGP();

		वापस map_fd_by_name(name, fds);
	पूर्ण अन्यथा अगर (is_prefix(**argv, "pinned")) अणु
		अक्षर *path;

		NEXT_ARGP();

		path = **argv;
		NEXT_ARGP();

		(*fds)[0] = खोलो_obj_pinned_any(path, BPF_OBJ_MAP);
		अगर ((*fds)[0] < 0)
			वापस -1;
		वापस 1;
	पूर्ण

	p_err("expected 'id', 'name' or 'pinned', got: '%s'?", **argv);
	वापस -1;
पूर्ण

पूर्णांक map_parse_fd(पूर्णांक *argc, अक्षर ***argv)
अणु
	पूर्णांक *fds = शून्य;
	पूर्णांक nb_fds, fd;

	fds = दो_स्मृति(माप(पूर्णांक));
	अगर (!fds) अणु
		p_err("mem alloc failed");
		वापस -1;
	पूर्ण
	nb_fds = map_parse_fds(argc, argv, &fds);
	अगर (nb_fds != 1) अणु
		अगर (nb_fds > 1) अणु
			p_err("several maps match this handle");
			जबतक (nb_fds--)
				बंद(fds[nb_fds]);
		पूर्ण
		fd = -1;
		जाओ निकास_मुक्त;
	पूर्ण

	fd = fds[0];
निकास_मुक्त:
	मुक्त(fds);
	वापस fd;
पूर्ण

पूर्णांक map_parse_fd_and_info(पूर्णांक *argc, अक्षर ***argv, व्योम *info, __u32 *info_len)
अणु
	पूर्णांक err;
	पूर्णांक fd;

	fd = map_parse_fd(argc, argv);
	अगर (fd < 0)
		वापस -1;

	err = bpf_obj_get_info_by_fd(fd, info, info_len);
	अगर (err) अणु
		p_err("can't get map info: %s", म_त्रुटि(त्रुटि_सं));
		बंद(fd);
		वापस err;
	पूर्ण

	वापस fd;
पूर्ण
