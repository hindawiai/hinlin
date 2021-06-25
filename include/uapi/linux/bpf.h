<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of version 2 of the GNU General Public
 * License as published by the Free Software Foundation.
 */
#अगर_अघोषित _UAPI__LINUX_BPF_H__
#घोषणा _UAPI__LINUX_BPF_H__

#समावेश <linux/types.h>
#समावेश <linux/bpf_common.h>

/* Extended inकाष्ठाion set based on top of classic BPF */

/* inकाष्ठाion classes */
#घोषणा BPF_JMP32	0x06	/* jmp mode in word width */
#घोषणा BPF_ALU64	0x07	/* alu mode in द्विगुन word width */

/* ld/ldx fields */
#घोषणा BPF_DW		0x18	/* द्विगुन word (64-bit) */
#घोषणा BPF_ATOMIC	0xc0	/* atomic memory ops - op type in immediate */
#घोषणा BPF_XADD	0xc0	/* exclusive add - legacy name */

/* alu/jmp fields */
#घोषणा BPF_MOV		0xb0	/* mov reg to reg */
#घोषणा BPF_ARSH	0xc0	/* sign extending arithmetic shअगरt right */

/* change endianness of a रेजिस्टर */
#घोषणा BPF_END		0xd0	/* flags क्रम endianness conversion: */
#घोषणा BPF_TO_LE	0x00	/* convert to little-endian */
#घोषणा BPF_TO_BE	0x08	/* convert to big-endian */
#घोषणा BPF_FROM_LE	BPF_TO_LE
#घोषणा BPF_FROM_BE	BPF_TO_BE

/* jmp encodings */
#घोषणा BPF_JNE		0x50	/* jump != */
#घोषणा BPF_JLT		0xa0	/* LT is अचिन्हित, '<' */
#घोषणा BPF_JLE		0xb0	/* LE is अचिन्हित, '<=' */
#घोषणा BPF_JSGT	0x60	/* SGT is चिन्हित '>', GT in x86 */
#घोषणा BPF_JSGE	0x70	/* SGE is चिन्हित '>=', GE in x86 */
#घोषणा BPF_JSLT	0xc0	/* SLT is चिन्हित, '<' */
#घोषणा BPF_JSLE	0xd0	/* SLE is चिन्हित, '<=' */
#घोषणा BPF_CALL	0x80	/* function call */
#घोषणा BPF_EXIT	0x90	/* function वापस */

/* atomic op type fields (stored in immediate) */
#घोषणा BPF_FETCH	0x01	/* not an opcode on its own, used to build others */
#घोषणा BPF_XCHG	(0xe0 | BPF_FETCH)	/* atomic exchange */
#घोषणा BPF_CMPXCHG	(0xf0 | BPF_FETCH)	/* atomic compare-and-ग_लिखो */

/* Register numbers */
क्रमागत अणु
	BPF_REG_0 = 0,
	BPF_REG_1,
	BPF_REG_2,
	BPF_REG_3,
	BPF_REG_4,
	BPF_REG_5,
	BPF_REG_6,
	BPF_REG_7,
	BPF_REG_8,
	BPF_REG_9,
	BPF_REG_10,
	__MAX_BPF_REG,
पूर्ण;

/* BPF has 10 general purpose 64-bit रेजिस्टरs and stack frame. */
#घोषणा MAX_BPF_REG	__MAX_BPF_REG

काष्ठा bpf_insn अणु
	__u8	code;		/* opcode */
	__u8	dst_reg:4;	/* dest रेजिस्टर */
	__u8	src_reg:4;	/* source रेजिस्टर */
	__s16	off;		/* चिन्हित offset */
	__s32	imm;		/* चिन्हित immediate स्थिरant */
पूर्ण;

/* Key of an a BPF_MAP_TYPE_LPM_TRIE entry */
काष्ठा bpf_lpm_trie_key अणु
	__u32	prefixlen;	/* up to 32 क्रम AF_INET, 128 क्रम AF_INET6 */
	__u8	data[0];	/* Arbitrary size */
पूर्ण;

काष्ठा bpf_cgroup_storage_key अणु
	__u64	cgroup_inode_id;	/* cgroup inode id */
	__u32	attach_type;		/* program attach type */
पूर्ण;

जोड़ bpf_iter_link_info अणु
	काष्ठा अणु
		__u32	map_fd;
	पूर्ण map;
पूर्ण;

/* BPF syscall commands, see bpf(2) man-page क्रम more details. */
/**
 * DOC: eBPF Syscall Preamble
 *
 * The operation to be perक्रमmed by the **bpf**\ () प्रणाली call is determined
 * by the *cmd* argument. Each operation takes an accompanying argument,
 * provided via *attr*, which is a poपूर्णांकer to a जोड़ of type *bpf_attr* (see
 * below). The size argument is the size of the जोड़ poपूर्णांकed to by *attr*.
 */
/**
 * DOC: eBPF Syscall Commands
 *
 * BPF_MAP_CREATE
 *	Description
 *		Create a map and वापस a file descriptor that refers to the
 *		map. The बंद-on-exec file descriptor flag (see **fcntl**\ (2))
 *		is स्वतःmatically enabled क्रम the new file descriptor.
 *
 *		Applying **बंद**\ (2) to the file descriptor वापसed by
 *		**BPF_MAP_CREATE** will delete the map (but see NOTES).
 *
 *	Return
 *		A new file descriptor (a nonnegative पूर्णांकeger), or -1 अगर an
 *		error occurred (in which हाल, *त्रुटि_सं* is set appropriately).
 *
 * BPF_MAP_LOOKUP_ELEM
 *	Description
 *		Look up an element with a given *key* in the map referred to
 *		by the file descriptor *map_fd*.
 *
 *		The *flags* argument may be specअगरied as one of the
 *		following:
 *
 *		**BPF_F_LOCK**
 *			Look up the value of a spin-locked map without
 *			वापसing the lock. This must be specअगरied अगर the
 *			elements contain a spinlock.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_MAP_UPDATE_ELEM
 *	Description
 *		Create or update an element (key/value pair) in a specअगरied map.
 *
 *		The *flags* argument should be specअगरied as one of the
 *		following:
 *
 *		**BPF_ANY**
 *			Create a new element or update an existing element.
 *		**BPF_NOEXIST**
 *			Create a new element only अगर it did not exist.
 *		**BPF_EXIST**
 *			Update an existing element.
 *		**BPF_F_LOCK**
 *			Update a spin_lock-ed map element.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 *		May set *त्रुटि_सं* to **EINVAL**, **EPERM**, **ENOMEM**,
 *		**E2BIG**, **EEXIST**, or **ENOENT**.
 *
 *		**E2BIG**
 *			The number of elements in the map reached the
 *			*max_entries* limit specअगरied at map creation समय.
 *		**EEXIST**
 *			If *flags* specअगरies **BPF_NOEXIST** and the element
 *			with *key* alपढ़ोy exists in the map.
 *		**ENOENT**
 *			If *flags* specअगरies **BPF_EXIST** and the element with
 *			*key* करोes not exist in the map.
 *
 * BPF_MAP_DELETE_ELEM
 *	Description
 *		Look up and delete an element by key in a specअगरied map.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_MAP_GET_NEXT_KEY
 *	Description
 *		Look up an element by key in a specअगरied map and वापस the key
 *		of the next element. Can be used to iterate over all elements
 *		in the map.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 *		The following हालs can be used to iterate over all elements of
 *		the map:
 *
 *		* If *key* is not found, the operation वापसs zero and sets
 *		  the *next_key* poपूर्णांकer to the key of the first element.
 *		* If *key* is found, the operation वापसs zero and sets the
 *		  *next_key* poपूर्णांकer to the key of the next element.
 *		* If *key* is the last element, वापसs -1 and *त्रुटि_सं* is set
 *		  to **ENOENT**.
 *
 *		May set *त्रुटि_सं* to **ENOMEM**, **EFAULT**, **EPERM**, or
 *		**EINVAL** on error.
 *
 * BPF_PROG_LOAD
 *	Description
 *		Verअगरy and load an eBPF program, वापसing a new file
 *		descriptor associated with the program.
 *
 *		Applying **बंद**\ (2) to the file descriptor वापसed by
 *		**BPF_PROG_LOAD** will unload the eBPF program (but see NOTES).
 *
 *		The बंद-on-exec file descriptor flag (see **fcntl**\ (2)) is
 *		स्वतःmatically enabled क्रम the new file descriptor.
 *
 *	Return
 *		A new file descriptor (a nonnegative पूर्णांकeger), or -1 अगर an
 *		error occurred (in which हाल, *त्रुटि_सं* is set appropriately).
 *
 * BPF_OBJ_PIN
 *	Description
 *		Pin an eBPF program or map referred by the specअगरied *bpf_fd*
 *		to the provided *pathname* on the fileप्रणाली.
 *
 *		The *pathname* argument must not contain a करोt (".").
 *
 *		On success, *pathname* retains a reference to the eBPF object,
 *		preventing deallocation of the object when the original
 *		*bpf_fd* is बंदd. This allow the eBPF object to live beyond
 *		**बंद**\ (\ *bpf_fd*\ ), and hence the lअगरeसमय of the parent
 *		process.
 *
 *		Applying **unlink**\ (2) or similar calls to the *pathname*
 *		unpins the object from the fileप्रणाली, removing the reference.
 *		If no other file descriptors or fileप्रणाली nodes refer to the
 *		same object, it will be deallocated (see NOTES).
 *
 *		The fileप्रणाली type क्रम the parent directory of *pathname* must
 *		be **BPF_FS_MAGIC**.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_OBJ_GET
 *	Description
 *		Open a file descriptor क्रम the eBPF object pinned to the
 *		specअगरied *pathname*.
 *
 *	Return
 *		A new file descriptor (a nonnegative पूर्णांकeger), or -1 अगर an
 *		error occurred (in which हाल, *त्रुटि_सं* is set appropriately).
 *
 * BPF_PROG_ATTACH
 *	Description
 *		Attach an eBPF program to a *target_fd* at the specअगरied
 *		*attach_type* hook.
 *
 *		The *attach_type* specअगरies the eBPF attachment poपूर्णांक to
 *		attach the program to, and must be one of *bpf_attach_type*
 *		(see below).
 *
 *		The *attach_bpf_fd* must be a valid file descriptor क्रम a
 *		loaded eBPF program of a cgroup, flow dissector, LIRC, sockmap
 *		or sock_ops type corresponding to the specअगरied *attach_type*.
 *
 *		The *target_fd* must be a valid file descriptor क्रम a kernel
 *		object which depends on the attach type of *attach_bpf_fd*:
 *
 *		**BPF_PROG_TYPE_CGROUP_DEVICE**,
 *		**BPF_PROG_TYPE_CGROUP_SKB**,
 *		**BPF_PROG_TYPE_CGROUP_SOCK**,
 *		**BPF_PROG_TYPE_CGROUP_SOCK_ADDR**,
 *		**BPF_PROG_TYPE_CGROUP_SOCKOPT**,
 *		**BPF_PROG_TYPE_CGROUP_SYSCTL**,
 *		**BPF_PROG_TYPE_SOCK_OPS**
 *
 *			Control Group v2 hierarchy with the eBPF controller
 *			enabled. Requires the kernel to be compiled with
 *			**CONFIG_CGROUP_BPF**.
 *
 *		**BPF_PROG_TYPE_FLOW_DISSECTOR**
 *
 *			Network namespace (eg /proc/self/ns/net).
 *
 *		**BPF_PROG_TYPE_LIRC_MODE2**
 *
 *			LIRC device path (eg /dev/lircN). Requires the kernel
 *			to be compiled with **CONFIG_BPF_LIRC_MODE2**.
 *
 *		**BPF_PROG_TYPE_SK_SKB**,
 *		**BPF_PROG_TYPE_SK_MSG**
 *
 *			eBPF map of socket type (eg **BPF_MAP_TYPE_SOCKHASH**).
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_PROG_DETACH
 *	Description
 *		Detach the eBPF program associated with the *target_fd* at the
 *		hook specअगरied by *attach_type*. The program must have been
 *		previously attached using **BPF_PROG_ATTACH**.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_PROG_TEST_RUN
 *	Description
 *		Run the eBPF program associated with the *prog_fd* a *repeat*
 *		number of बार against a provided program context *ctx_in* and
 *		data *data_in*, and वापस the modअगरied program context
 *		*ctx_out*, *data_out* (क्रम example, packet data), result of the
 *		execution *retval*, and *duration* of the test run.
 *
 *		The sizes of the buffers provided as input and output
 *		parameters *ctx_in*, *ctx_out*, *data_in*, and *data_out* must
 *		be provided in the corresponding variables *ctx_size_in*,
 *		*ctx_size_out*, *data_size_in*, and/or *data_size_out*. If any
 *		of these parameters are not provided (ie set to शून्य), the
 *		corresponding size field must be zero.
 *
 *		Some program types have particular requirements:
 *
 *		**BPF_PROG_TYPE_SK_LOOKUP**
 *			*data_in* and *data_out* must be शून्य.
 *
 *		**BPF_PROG_TYPE_XDP**
 *			*ctx_in* and *ctx_out* must be शून्य.
 *
 *		**BPF_PROG_TYPE_RAW_TRACEPOINT**,
 *		**BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE**
 *
 *			*ctx_out*, *data_in* and *data_out* must be शून्य.
 *			*repeat* must be zero.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 *		**ENOSPC**
 *			Either *data_size_out* or *ctx_size_out* is too small.
 *		**ENOTSUPP**
 *			This command is not supported by the program type of
 *			the program referred to by *prog_fd*.
 *
 * BPF_PROG_GET_NEXT_ID
 *	Description
 *		Fetch the next eBPF program currently loaded पूर्णांकo the kernel.
 *
 *		Looks क्रम the eBPF program with an id greater than *start_id*
 *		and updates *next_id* on success. If no other eBPF programs
 *		reमुख्य with ids higher than *start_id*, वापसs -1 and sets
 *		*त्रुटि_सं* to **ENOENT**.
 *
 *	Return
 *		Returns zero on success. On error, or when no id reमुख्यs, -1
 *		is वापसed and *त्रुटि_सं* is set appropriately.
 *
 * BPF_MAP_GET_NEXT_ID
 *	Description
 *		Fetch the next eBPF map currently loaded पूर्णांकo the kernel.
 *
 *		Looks क्रम the eBPF map with an id greater than *start_id*
 *		and updates *next_id* on success. If no other eBPF maps
 *		reमुख्य with ids higher than *start_id*, वापसs -1 and sets
 *		*त्रुटि_सं* to **ENOENT**.
 *
 *	Return
 *		Returns zero on success. On error, or when no id reमुख्यs, -1
 *		is वापसed and *त्रुटि_सं* is set appropriately.
 *
 * BPF_PROG_GET_FD_BY_ID
 *	Description
 *		Open a file descriptor क्रम the eBPF program corresponding to
 *		*prog_id*.
 *
 *	Return
 *		A new file descriptor (a nonnegative पूर्णांकeger), or -1 अगर an
 *		error occurred (in which हाल, *त्रुटि_सं* is set appropriately).
 *
 * BPF_MAP_GET_FD_BY_ID
 *	Description
 *		Open a file descriptor क्रम the eBPF map corresponding to
 *		*map_id*.
 *
 *	Return
 *		A new file descriptor (a nonnegative पूर्णांकeger), or -1 अगर an
 *		error occurred (in which हाल, *त्रुटि_सं* is set appropriately).
 *
 * BPF_OBJ_GET_INFO_BY_FD
 *	Description
 *		Obtain inक्रमmation about the eBPF object corresponding to
 *		*bpf_fd*.
 *
 *		Populates up to *info_len* bytes of *info*, which will be in
 *		one of the following क्रमmats depending on the eBPF object type
 *		of *bpf_fd*:
 *
 *		* **काष्ठा bpf_prog_info**
 *		* **काष्ठा bpf_map_info**
 *		* **काष्ठा bpf_btf_info**
 *		* **काष्ठा bpf_link_info**
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_PROG_QUERY
 *	Description
 *		Obtain inक्रमmation about eBPF programs associated with the
 *		specअगरied *attach_type* hook.
 *
 *		The *target_fd* must be a valid file descriptor क्रम a kernel
 *		object which depends on the attach type of *attach_bpf_fd*:
 *
 *		**BPF_PROG_TYPE_CGROUP_DEVICE**,
 *		**BPF_PROG_TYPE_CGROUP_SKB**,
 *		**BPF_PROG_TYPE_CGROUP_SOCK**,
 *		**BPF_PROG_TYPE_CGROUP_SOCK_ADDR**,
 *		**BPF_PROG_TYPE_CGROUP_SOCKOPT**,
 *		**BPF_PROG_TYPE_CGROUP_SYSCTL**,
 *		**BPF_PROG_TYPE_SOCK_OPS**
 *
 *			Control Group v2 hierarchy with the eBPF controller
 *			enabled. Requires the kernel to be compiled with
 *			**CONFIG_CGROUP_BPF**.
 *
 *		**BPF_PROG_TYPE_FLOW_DISSECTOR**
 *
 *			Network namespace (eg /proc/self/ns/net).
 *
 *		**BPF_PROG_TYPE_LIRC_MODE2**
 *
 *			LIRC device path (eg /dev/lircN). Requires the kernel
 *			to be compiled with **CONFIG_BPF_LIRC_MODE2**.
 *
 *		**BPF_PROG_QUERY** always fetches the number of programs
 *		attached and the *attach_flags* which were used to attach those
 *		programs. Additionally, अगर *prog_ids* is nonzero and the number
 *		of attached programs is less than *prog_cnt*, populates
 *		*prog_ids* with the eBPF program ids of the programs attached
 *		at *target_fd*.
 *
 *		The following flags may alter the result:
 *
 *		**BPF_F_QUERY_EFFECTIVE**
 *			Only वापस inक्रमmation regarding programs which are
 *			currently effective at the specअगरied *target_fd*.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_RAW_TRACEPOINT_OPEN
 *	Description
 *		Attach an eBPF program to a tracepoपूर्णांक *name* to access kernel
 *		पूर्णांकernal arguments of the tracepoपूर्णांक in their raw क्रमm.
 *
 *		The *prog_fd* must be a valid file descriptor associated with
 *		a loaded eBPF program of type **BPF_PROG_TYPE_RAW_TRACEPOINT**.
 *
 *		No ABI guarantees are made about the content of tracepoपूर्णांक
 *		arguments exposed to the corresponding eBPF program.
 *
 *		Applying **बंद**\ (2) to the file descriptor वापसed by
 *		**BPF_RAW_TRACEPOINT_OPEN** will delete the map (but see NOTES).
 *
 *	Return
 *		A new file descriptor (a nonnegative पूर्णांकeger), or -1 अगर an
 *		error occurred (in which हाल, *त्रुटि_सं* is set appropriately).
 *
 * BPF_BTF_LOAD
 *	Description
 *		Verअगरy and load BPF Type Format (BTF) metadata पूर्णांकo the kernel,
 *		वापसing a new file descriptor associated with the metadata.
 *		BTF is described in more detail at
 *		https://www.kernel.org/करोc/hपंचांगl/latest/bpf/btf.hपंचांगl.
 *
 *		The *btf* parameter must poपूर्णांक to valid memory providing
 *		*btf_size* bytes of BTF binary metadata.
 *
 *		The वापसed file descriptor can be passed to other **bpf**\ ()
 *		subcommands such as **BPF_PROG_LOAD** or **BPF_MAP_CREATE** to
 *		associate the BTF with those objects.
 *
 *		Similar to **BPF_PROG_LOAD**, **BPF_BTF_LOAD** has optional
 *		parameters to specअगरy a *btf_log_buf*, *btf_log_size* and
 *		*btf_log_level* which allow the kernel to वापस मुक्तक्रमm log
 *		output regarding the BTF verअगरication process.
 *
 *	Return
 *		A new file descriptor (a nonnegative पूर्णांकeger), or -1 अगर an
 *		error occurred (in which हाल, *त्रुटि_सं* is set appropriately).
 *
 * BPF_BTF_GET_FD_BY_ID
 *	Description
 *		Open a file descriptor क्रम the BPF Type Format (BTF)
 *		corresponding to *btf_id*.
 *
 *	Return
 *		A new file descriptor (a nonnegative पूर्णांकeger), or -1 अगर an
 *		error occurred (in which हाल, *त्रुटि_सं* is set appropriately).
 *
 * BPF_TASK_FD_QUERY
 *	Description
 *		Obtain inक्रमmation about eBPF programs associated with the
 *		target process identअगरied by *pid* and *fd*.
 *
 *		If the *pid* and *fd* are associated with a tracepoपूर्णांक, kprobe
 *		or uprobe perf event, then the *prog_id* and *fd_type* will
 *		be populated with the eBPF program id and file descriptor type
 *		of type **bpf_task_fd_type**. If associated with a kprobe or
 *		uprobe, the  *probe_offset* and *probe_addr* will also be
 *		populated. Optionally, अगर *buf* is provided, then up to
 *		*buf_len* bytes of *buf* will be populated with the name of
 *		the tracepoपूर्णांक, kprobe or uprobe.
 *
 *		The resulting *prog_id* may be पूर्णांकrospected in deeper detail
 *		using **BPF_PROG_GET_FD_BY_ID** and **BPF_OBJ_GET_INFO_BY_FD**.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_MAP_LOOKUP_AND_DELETE_ELEM
 *	Description
 *		Look up an element with the given *key* in the map referred to
 *		by the file descriptor *fd*, and अगर found, delete the element.
 *
 *		The **BPF_MAP_TYPE_QUEUE** and **BPF_MAP_TYPE_STACK** map types
 *		implement this command as a "pop" operation, deleting the top
 *		element rather than one corresponding to *key*.
 *		The *key* and *key_len* parameters should be zeroed when
 *		issuing this operation क्रम these map types.
 *
 *		This command is only valid क्रम the following map types:
 *		* **BPF_MAP_TYPE_QUEUE**
 *		* **BPF_MAP_TYPE_STACK**
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_MAP_FREEZE
 *	Description
 *		Freeze the permissions of the specअगरied map.
 *
 *		Write permissions may be frozen by passing zero *flags*.
 *		Upon success, no future syscall invocations may alter the
 *		map state of *map_fd*. Write operations from eBPF programs
 *		are still possible क्रम a frozen map.
 *
 *		Not supported क्रम maps of type **BPF_MAP_TYPE_STRUCT_OPS**.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_BTF_GET_NEXT_ID
 *	Description
 *		Fetch the next BPF Type Format (BTF) object currently loaded
 *		पूर्णांकo the kernel.
 *
 *		Looks क्रम the BTF object with an id greater than *start_id*
 *		and updates *next_id* on success. If no other BTF objects
 *		reमुख्य with ids higher than *start_id*, वापसs -1 and sets
 *		*त्रुटि_सं* to **ENOENT**.
 *
 *	Return
 *		Returns zero on success. On error, or when no id reमुख्यs, -1
 *		is वापसed and *त्रुटि_सं* is set appropriately.
 *
 * BPF_MAP_LOOKUP_BATCH
 *	Description
 *		Iterate and fetch multiple elements in a map.
 *
 *		Two opaque values are used to manage batch operations,
 *		*in_batch* and *out_batch*. Initially, *in_batch* must be set
 *		to शून्य to begin the batched operation. After each subsequent
 *		**BPF_MAP_LOOKUP_BATCH**, the caller should pass the resultant
 *		*out_batch* as the *in_batch* क्रम the next operation to
 *		जारी iteration from the current poपूर्णांक.
 *
 *		The *keys* and *values* are output parameters which must poपूर्णांक
 *		to memory large enough to hold *count* items based on the key
 *		and value size of the map *map_fd*. The *keys* buffer must be
 *		of *key_size* * *count*. The *values* buffer must be of
 *		*value_size* * *count*.
 *
 *		The *elem_flags* argument may be specअगरied as one of the
 *		following:
 *
 *		**BPF_F_LOCK**
 *			Look up the value of a spin-locked map without
 *			वापसing the lock. This must be specअगरied अगर the
 *			elements contain a spinlock.
 *
 *		On success, *count* elements from the map are copied पूर्णांकo the
 *		user buffer, with the keys copied पूर्णांकo *keys* and the values
 *		copied पूर्णांकo the corresponding indices in *values*.
 *
 *		If an error is वापसed and *त्रुटि_सं* is not **EFAULT**, *count*
 *		is set to the number of successfully processed elements.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 *		May set *त्रुटि_सं* to **ENOSPC** to indicate that *keys* or
 *		*values* is too small to dump an entire bucket during
 *		iteration of a hash-based map type.
 *
 * BPF_MAP_LOOKUP_AND_DELETE_BATCH
 *	Description
 *		Iterate and delete all elements in a map.
 *
 *		This operation has the same behavior as
 *		**BPF_MAP_LOOKUP_BATCH** with two exceptions:
 *
 *		* Every element that is successfully वापसed is also deleted
 *		  from the map. This is at least *count* elements. Note that
 *		  *count* is both an input and an output parameter.
 *		* Upon वापसing with *त्रुटि_सं* set to **EFAULT**, up to
 *		  *count* elements may be deleted without वापसing the keys
 *		  and values of the deleted elements.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_MAP_UPDATE_BATCH
 *	Description
 *		Update multiple elements in a map by *key*.
 *
 *		The *keys* and *values* are input parameters which must poपूर्णांक
 *		to memory large enough to hold *count* items based on the key
 *		and value size of the map *map_fd*. The *keys* buffer must be
 *		of *key_size* * *count*. The *values* buffer must be of
 *		*value_size* * *count*.
 *
 *		Each element specअगरied in *keys* is sequentially updated to the
 *		value in the corresponding index in *values*. The *in_batch*
 *		and *out_batch* parameters are ignored and should be zeroed.
 *
 *		The *elem_flags* argument should be specअगरied as one of the
 *		following:
 *
 *		**BPF_ANY**
 *			Create new elements or update a existing elements.
 *		**BPF_NOEXIST**
 *			Create new elements only अगर they करो not exist.
 *		**BPF_EXIST**
 *			Update existing elements.
 *		**BPF_F_LOCK**
 *			Update spin_lock-ed map elements. This must be
 *			specअगरied अगर the map value contains a spinlock.
 *
 *		On success, *count* elements from the map are updated.
 *
 *		If an error is वापसed and *त्रुटि_सं* is not **EFAULT**, *count*
 *		is set to the number of successfully processed elements.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 *		May set *त्रुटि_सं* to **EINVAL**, **EPERM**, **ENOMEM**, or
 *		**E2BIG**. **E2BIG** indicates that the number of elements in
 *		the map reached the *max_entries* limit specअगरied at map
 *		creation समय.
 *
 *		May set *त्रुटि_सं* to one of the following error codes under
 *		specअगरic circumstances:
 *
 *		**EEXIST**
 *			If *flags* specअगरies **BPF_NOEXIST** and the element
 *			with *key* alपढ़ोy exists in the map.
 *		**ENOENT**
 *			If *flags* specअगरies **BPF_EXIST** and the element with
 *			*key* करोes not exist in the map.
 *
 * BPF_MAP_DELETE_BATCH
 *	Description
 *		Delete multiple elements in a map by *key*.
 *
 *		The *keys* parameter is an input parameter which must poपूर्णांक
 *		to memory large enough to hold *count* items based on the key
 *		size of the map *map_fd*, that is, *key_size* * *count*.
 *
 *		Each element specअगरied in *keys* is sequentially deleted. The
 *		*in_batch*, *out_batch*, and *values* parameters are ignored
 *		and should be zeroed.
 *
 *		The *elem_flags* argument may be specअगरied as one of the
 *		following:
 *
 *		**BPF_F_LOCK**
 *			Look up the value of a spin-locked map without
 *			वापसing the lock. This must be specअगरied अगर the
 *			elements contain a spinlock.
 *
 *		On success, *count* elements from the map are updated.
 *
 *		If an error is वापसed and *त्रुटि_सं* is not **EFAULT**, *count*
 *		is set to the number of successfully processed elements. If
 *		*त्रुटि_सं* is **EFAULT**, up to *count* elements may be been
 *		deleted.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_LINK_CREATE
 *	Description
 *		Attach an eBPF program to a *target_fd* at the specअगरied
 *		*attach_type* hook and वापस a file descriptor handle क्रम
 *		managing the link.
 *
 *	Return
 *		A new file descriptor (a nonnegative पूर्णांकeger), or -1 अगर an
 *		error occurred (in which हाल, *त्रुटि_सं* is set appropriately).
 *
 * BPF_LINK_UPDATE
 *	Description
 *		Update the eBPF program in the specअगरied *link_fd* to
 *		*new_prog_fd*.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_LINK_GET_FD_BY_ID
 *	Description
 *		Open a file descriptor क्रम the eBPF Link corresponding to
 *		*link_id*.
 *
 *	Return
 *		A new file descriptor (a nonnegative पूर्णांकeger), or -1 अगर an
 *		error occurred (in which हाल, *त्रुटि_सं* is set appropriately).
 *
 * BPF_LINK_GET_NEXT_ID
 *	Description
 *		Fetch the next eBPF link currently loaded पूर्णांकo the kernel.
 *
 *		Looks क्रम the eBPF link with an id greater than *start_id*
 *		and updates *next_id* on success. If no other eBPF links
 *		reमुख्य with ids higher than *start_id*, वापसs -1 and sets
 *		*त्रुटि_सं* to **ENOENT**.
 *
 *	Return
 *		Returns zero on success. On error, or when no id reमुख्यs, -1
 *		is वापसed and *त्रुटि_सं* is set appropriately.
 *
 * BPF_ENABLE_STATS
 *	Description
 *		Enable eBPF runसमय statistics gathering.
 *
 *		Runसमय statistics gathering क्रम the eBPF runसमय is disabled
 *		by शेष to minimize the corresponding perक्रमmance overhead.
 *		This command enables statistics globally.
 *
 *		Multiple programs may independently enable statistics.
 *		After gathering the desired statistics, eBPF runसमय statistics
 *		may be disabled again by calling **बंद**\ (2) क्रम the file
 *		descriptor वापसed by this function. Statistics will only be
 *		disabled प्रणाली-wide when all outstanding file descriptors
 *		वापसed by prior calls क्रम this subcommand are बंदd.
 *
 *	Return
 *		A new file descriptor (a nonnegative पूर्णांकeger), or -1 अगर an
 *		error occurred (in which हाल, *त्रुटि_सं* is set appropriately).
 *
 * BPF_ITER_CREATE
 *	Description
 *		Create an iterator on top of the specअगरied *link_fd* (as
 *		previously created using **BPF_LINK_CREATE**) and वापस a
 *		file descriptor that can be used to trigger the iteration.
 *
 *		If the resulting file descriptor is pinned to the fileप्रणाली
 *		using  **BPF_OBJ_PIN**, then subsequent **पढ़ो**\ (2) syscalls
 *		क्रम that path will trigger the iterator to पढ़ो kernel state
 *		using the eBPF program attached to *link_fd*.
 *
 *	Return
 *		A new file descriptor (a nonnegative पूर्णांकeger), or -1 अगर an
 *		error occurred (in which हाल, *त्रुटि_सं* is set appropriately).
 *
 * BPF_LINK_DETACH
 *	Description
 *		Forcefully detach the specअगरied *link_fd* from its
 *		corresponding attachment poपूर्णांक.
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * BPF_PROG_BIND_MAP
 *	Description
 *		Bind a map to the lअगरeसमय of an eBPF program.
 *
 *		The map identअगरied by *map_fd* is bound to the program
 *		identअगरied by *prog_fd* and only released when *prog_fd* is
 *		released. This may be used in हालs where metadata should be
 *		associated with a program which otherwise करोes not contain any
 *		references to the map (क्रम example, embedded in the eBPF
 *		program inकाष्ठाions).
 *
 *	Return
 *		Returns zero on success. On error, -1 is वापसed and *त्रुटि_सं*
 *		is set appropriately.
 *
 * NOTES
 *	eBPF objects (maps and programs) can be shared between processes.
 *
 *	* After **विभाजन**\ (2), the child inherits file descriptors
 *	  referring to the same eBPF objects.
 *	* File descriptors referring to eBPF objects can be transferred over
 *	  **unix**\ (7) करोमुख्य sockets.
 *	* File descriptors referring to eBPF objects can be duplicated in the
 *	  usual way, using **dup**\ (2) and similar calls.
 *	* File descriptors referring to eBPF objects can be pinned to the
 *	  fileप्रणाली using the **BPF_OBJ_PIN** command of **bpf**\ (2).
 *
 *	An eBPF object is deallocated only after all file descriptors referring
 *	to the object have been बंदd and no references reमुख्य pinned to the
 *	fileप्रणाली or attached (क्रम example, bound to a program or device).
 */
क्रमागत bpf_cmd अणु
	BPF_MAP_CREATE,
	BPF_MAP_LOOKUP_ELEM,
	BPF_MAP_UPDATE_ELEM,
	BPF_MAP_DELETE_ELEM,
	BPF_MAP_GET_NEXT_KEY,
	BPF_PROG_LOAD,
	BPF_OBJ_PIN,
	BPF_OBJ_GET,
	BPF_PROG_ATTACH,
	BPF_PROG_DETACH,
	BPF_PROG_TEST_RUN,
	BPF_PROG_GET_NEXT_ID,
	BPF_MAP_GET_NEXT_ID,
	BPF_PROG_GET_FD_BY_ID,
	BPF_MAP_GET_FD_BY_ID,
	BPF_OBJ_GET_INFO_BY_FD,
	BPF_PROG_QUERY,
	BPF_RAW_TRACEPOINT_OPEN,
	BPF_BTF_LOAD,
	BPF_BTF_GET_FD_BY_ID,
	BPF_TASK_FD_QUERY,
	BPF_MAP_LOOKUP_AND_DELETE_ELEM,
	BPF_MAP_FREEZE,
	BPF_BTF_GET_NEXT_ID,
	BPF_MAP_LOOKUP_BATCH,
	BPF_MAP_LOOKUP_AND_DELETE_BATCH,
	BPF_MAP_UPDATE_BATCH,
	BPF_MAP_DELETE_BATCH,
	BPF_LINK_CREATE,
	BPF_LINK_UPDATE,
	BPF_LINK_GET_FD_BY_ID,
	BPF_LINK_GET_NEXT_ID,
	BPF_ENABLE_STATS,
	BPF_ITER_CREATE,
	BPF_LINK_DETACH,
	BPF_PROG_BIND_MAP,
पूर्ण;

क्रमागत bpf_map_type अणु
	BPF_MAP_TYPE_UNSPEC,
	BPF_MAP_TYPE_HASH,
	BPF_MAP_TYPE_ARRAY,
	BPF_MAP_TYPE_PROG_ARRAY,
	BPF_MAP_TYPE_PERF_EVENT_ARRAY,
	BPF_MAP_TYPE_PERCPU_HASH,
	BPF_MAP_TYPE_PERCPU_ARRAY,
	BPF_MAP_TYPE_STACK_TRACE,
	BPF_MAP_TYPE_CGROUP_ARRAY,
	BPF_MAP_TYPE_LRU_HASH,
	BPF_MAP_TYPE_LRU_PERCPU_HASH,
	BPF_MAP_TYPE_LPM_TRIE,
	BPF_MAP_TYPE_ARRAY_OF_MAPS,
	BPF_MAP_TYPE_HASH_OF_MAPS,
	BPF_MAP_TYPE_DEVMAP,
	BPF_MAP_TYPE_SOCKMAP,
	BPF_MAP_TYPE_CPUMAP,
	BPF_MAP_TYPE_XSKMAP,
	BPF_MAP_TYPE_SOCKHASH,
	BPF_MAP_TYPE_CGROUP_STORAGE,
	BPF_MAP_TYPE_REUSEPORT_SOCKARRAY,
	BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE,
	BPF_MAP_TYPE_QUEUE,
	BPF_MAP_TYPE_STACK,
	BPF_MAP_TYPE_SK_STORAGE,
	BPF_MAP_TYPE_DEVMAP_HASH,
	BPF_MAP_TYPE_STRUCT_OPS,
	BPF_MAP_TYPE_RINGBUF,
	BPF_MAP_TYPE_INODE_STORAGE,
	BPF_MAP_TYPE_TASK_STORAGE,
पूर्ण;

/* Note that tracing related programs such as
 * BPF_PROG_TYPE_अणुKPROBE,TRACEPOINT,PERF_EVENT,RAW_TRACEPOINTपूर्ण
 * are not subject to a stable API since kernel पूर्णांकernal data
 * काष्ठाures can change from release to release and may
 * thereक्रमe अवरोध existing tracing BPF programs. Tracing BPF
 * programs correspond to /a/ specअगरic kernel which is to be
 * analyzed, and not /a/ specअगरic kernel /and/ all future ones.
 */
क्रमागत bpf_prog_type अणु
	BPF_PROG_TYPE_UNSPEC,
	BPF_PROG_TYPE_SOCKET_FILTER,
	BPF_PROG_TYPE_KPROBE,
	BPF_PROG_TYPE_SCHED_CLS,
	BPF_PROG_TYPE_SCHED_ACT,
	BPF_PROG_TYPE_TRACEPOINT,
	BPF_PROG_TYPE_XDP,
	BPF_PROG_TYPE_PERF_EVENT,
	BPF_PROG_TYPE_CGROUP_SKB,
	BPF_PROG_TYPE_CGROUP_SOCK,
	BPF_PROG_TYPE_LWT_IN,
	BPF_PROG_TYPE_LWT_OUT,
	BPF_PROG_TYPE_LWT_XMIT,
	BPF_PROG_TYPE_SOCK_OPS,
	BPF_PROG_TYPE_SK_SKB,
	BPF_PROG_TYPE_CGROUP_DEVICE,
	BPF_PROG_TYPE_SK_MSG,
	BPF_PROG_TYPE_RAW_TRACEPOINT,
	BPF_PROG_TYPE_CGROUP_SOCK_ADDR,
	BPF_PROG_TYPE_LWT_SEG6LOCAL,
	BPF_PROG_TYPE_LIRC_MODE2,
	BPF_PROG_TYPE_SK_REUSEPORT,
	BPF_PROG_TYPE_FLOW_DISSECTOR,
	BPF_PROG_TYPE_CGROUP_SYSCTL,
	BPF_PROG_TYPE_RAW_TRACEPOINT_WRITABLE,
	BPF_PROG_TYPE_CGROUP_SOCKOPT,
	BPF_PROG_TYPE_TRACING,
	BPF_PROG_TYPE_STRUCT_OPS,
	BPF_PROG_TYPE_EXT,
	BPF_PROG_TYPE_LSM,
	BPF_PROG_TYPE_SK_LOOKUP,
पूर्ण;

क्रमागत bpf_attach_type अणु
	BPF_CGROUP_INET_INGRESS,
	BPF_CGROUP_INET_EGRESS,
	BPF_CGROUP_INET_SOCK_CREATE,
	BPF_CGROUP_SOCK_OPS,
	BPF_SK_SKB_STREAM_PARSER,
	BPF_SK_SKB_STREAM_VERDICT,
	BPF_CGROUP_DEVICE,
	BPF_SK_MSG_VERDICT,
	BPF_CGROUP_INET4_BIND,
	BPF_CGROUP_INET6_BIND,
	BPF_CGROUP_INET4_CONNECT,
	BPF_CGROUP_INET6_CONNECT,
	BPF_CGROUP_INET4_POST_BIND,
	BPF_CGROUP_INET6_POST_BIND,
	BPF_CGROUP_UDP4_SENDMSG,
	BPF_CGROUP_UDP6_SENDMSG,
	BPF_LIRC_MODE2,
	BPF_FLOW_DISSECTOR,
	BPF_CGROUP_SYSCTL,
	BPF_CGROUP_UDP4_RECVMSG,
	BPF_CGROUP_UDP6_RECVMSG,
	BPF_CGROUP_GETSOCKOPT,
	BPF_CGROUP_SETSOCKOPT,
	BPF_TRACE_RAW_TP,
	BPF_TRACE_FENTRY,
	BPF_TRACE_FEXIT,
	BPF_MODIFY_RETURN,
	BPF_LSM_MAC,
	BPF_TRACE_ITER,
	BPF_CGROUP_INET4_GETPEERNAME,
	BPF_CGROUP_INET6_GETPEERNAME,
	BPF_CGROUP_INET4_GETSOCKNAME,
	BPF_CGROUP_INET6_GETSOCKNAME,
	BPF_XDP_DEVMAP,
	BPF_CGROUP_INET_SOCK_RELEASE,
	BPF_XDP_CPUMAP,
	BPF_SK_LOOKUP,
	BPF_XDP,
	BPF_SK_SKB_VERDICT,
	__MAX_BPF_ATTACH_TYPE
पूर्ण;

#घोषणा MAX_BPF_ATTACH_TYPE __MAX_BPF_ATTACH_TYPE

क्रमागत bpf_link_type अणु
	BPF_LINK_TYPE_UNSPEC = 0,
	BPF_LINK_TYPE_RAW_TRACEPOINT = 1,
	BPF_LINK_TYPE_TRACING = 2,
	BPF_LINK_TYPE_CGROUP = 3,
	BPF_LINK_TYPE_ITER = 4,
	BPF_LINK_TYPE_NETNS = 5,
	BPF_LINK_TYPE_XDP = 6,

	MAX_BPF_LINK_TYPE,
पूर्ण;

/* cgroup-bpf attach flags used in BPF_PROG_ATTACH command
 *
 * NONE(शेष): No further bpf programs allowed in the subtree.
 *
 * BPF_F_ALLOW_OVERRIDE: If a sub-cgroup installs some bpf program,
 * the program in this cgroup yields to sub-cgroup program.
 *
 * BPF_F_ALLOW_MULTI: If a sub-cgroup installs some bpf program,
 * that cgroup program माला_लो run in addition to the program in this cgroup.
 *
 * Only one program is allowed to be attached to a cgroup with
 * NONE or BPF_F_ALLOW_OVERRIDE flag.
 * Attaching another program on top of NONE or BPF_F_ALLOW_OVERRIDE will
 * release old program and attach the new one. Attach flags has to match.
 *
 * Multiple programs are allowed to be attached to a cgroup with
 * BPF_F_ALLOW_MULTI flag. They are executed in FIFO order
 * (those that were attached first, run first)
 * The programs of sub-cgroup are executed first, then programs of
 * this cgroup and then programs of parent cgroup.
 * When children program makes decision (like picking TCP CA or sock bind)
 * parent program has a chance to override it.
 *
 * With BPF_F_ALLOW_MULTI a new program is added to the end of the list of
 * programs क्रम a cgroup. Though it's possible to replace an old program at
 * any position by also specअगरying BPF_F_REPLACE flag and position itself in
 * replace_bpf_fd attribute. Old program at this position will be released.
 *
 * A cgroup with MULTI or OVERRIDE flag allows any attach flags in sub-cgroups.
 * A cgroup with NONE करोesn't allow any programs in sub-cgroups.
 * Ex1:
 * cgrp1 (MULTI progs A, B) ->
 *    cgrp2 (OVERRIDE prog C) ->
 *      cgrp3 (MULTI prog D) ->
 *        cgrp4 (OVERRIDE prog E) ->
 *          cgrp5 (NONE prog F)
 * the event in cgrp5 triggers execution of F,D,A,B in that order.
 * अगर prog F is detached, the execution is E,D,A,B
 * अगर prog F and D are detached, the execution is E,A,B
 * अगर prog F, E and D are detached, the execution is C,A,B
 *
 * All eligible programs are executed regardless of वापस code from
 * earlier programs.
 */
#घोषणा BPF_F_ALLOW_OVERRIDE	(1U << 0)
#घोषणा BPF_F_ALLOW_MULTI	(1U << 1)
#घोषणा BPF_F_REPLACE		(1U << 2)

/* If BPF_F_STRICT_ALIGNMENT is used in BPF_PROG_LOAD command, the
 * verअगरier will perक्रमm strict alignment checking as अगर the kernel
 * has been built with CONFIG_EFFICIENT_UNALIGNED_ACCESS not set,
 * and NET_IP_ALIGN defined to 2.
 */
#घोषणा BPF_F_STRICT_ALIGNMENT	(1U << 0)

/* If BPF_F_ANY_ALIGNMENT is used in BPF_PROF_LOAD command, the
 * verअगरier will allow any alignment whatsoever.  On platक्रमms
 * with strict alignment requirements क्रम loads ands stores (such
 * as sparc and mips) the verअगरier validates that all loads and
 * stores provably follow this requirement.  This flag turns that
 * checking and enक्रमcement off.
 *
 * It is mostly used क्रम testing when we want to validate the
 * context and memory access aspects of the verअगरier, but because
 * of an unaligned access the alignment check would trigger beक्रमe
 * the one we are पूर्णांकerested in.
 */
#घोषणा BPF_F_ANY_ALIGNMENT	(1U << 1)

/* BPF_F_TEST_RND_HI32 is used in BPF_PROG_LOAD command क्रम testing purpose.
 * Verअगरier करोes sub-रेजिस्टर def/use analysis and identअगरies inकाष्ठाions whose
 * def only matters क्रम low 32-bit, high 32-bit is never referenced later
 * through implicit zero extension. Thereक्रमe verअगरier notअगरies JIT back-ends
 * that it is safe to ignore clearing high 32-bit क्रम these inकाष्ठाions. This
 * saves some back-ends a lot of code-gen. However such optimization is not
 * necessary on some arches, क्रम example x86_64, arm64 etc, whose JIT back-ends
 * hence hasn't used verifier's analysis result. But, we really want to have a
 * way to be able to verअगरy the correctness of the described optimization on
 * x86_64 on which testsuites are frequently exercised.
 *
 * So, this flag is पूर्णांकroduced. Once it is set, verअगरier will अक्रमomize high
 * 32-bit क्रम those inकाष्ठाions who has been identअगरied as safe to ignore them.
 * Then, अगर verअगरier is not करोing correct analysis, such अक्रमomization will
 * regress tests to expose bugs.
 */
#घोषणा BPF_F_TEST_RND_HI32	(1U << 2)

/* The verअगरier पूर्णांकernal test flag. Behavior is undefined */
#घोषणा BPF_F_TEST_STATE_FREQ	(1U << 3)

/* If BPF_F_SLEEPABLE is used in BPF_PROG_LOAD command, the verअगरier will
 * restrict map and helper usage क्रम such programs. Sleepable BPF programs can
 * only be attached to hooks where kernel execution context allows sleeping.
 * Such programs are allowed to use helpers that may sleep like
 * bpf_copy_from_user().
 */
#घोषणा BPF_F_SLEEPABLE		(1U << 4)

/* When BPF ldimm64's insn[0].src_reg != 0 then this can have
 * the following extensions:
 *
 * insn[0].src_reg:  BPF_PSEUDO_MAP_FD
 * insn[0].imm:      map fd
 * insn[1].imm:      0
 * insn[0].off:      0
 * insn[1].off:      0
 * ldimm64 reग_लिखो:  address of map
 * verअगरier type:    CONST_PTR_TO_MAP
 */
#घोषणा BPF_PSEUDO_MAP_FD	1
/* insn[0].src_reg:  BPF_PSEUDO_MAP_VALUE
 * insn[0].imm:      map fd
 * insn[1].imm:      offset पूर्णांकo value
 * insn[0].off:      0
 * insn[1].off:      0
 * ldimm64 reग_लिखो:  address of map[0]+offset
 * verअगरier type:    PTR_TO_MAP_VALUE
 */
#घोषणा BPF_PSEUDO_MAP_VALUE	2
/* insn[0].src_reg:  BPF_PSEUDO_BTF_ID
 * insn[0].imm:      kernel btd id of VAR
 * insn[1].imm:      0
 * insn[0].off:      0
 * insn[1].off:      0
 * ldimm64 reग_लिखो:  address of the kernel variable
 * verअगरier type:    PTR_TO_BTF_ID or PTR_TO_MEM, depending on whether the var
 *                   is काष्ठा/जोड़.
 */
#घोषणा BPF_PSEUDO_BTF_ID	3
/* insn[0].src_reg:  BPF_PSEUDO_FUNC
 * insn[0].imm:      insn offset to the func
 * insn[1].imm:      0
 * insn[0].off:      0
 * insn[1].off:      0
 * ldimm64 reग_लिखो:  address of the function
 * verअगरier type:    PTR_TO_FUNC.
 */
#घोषणा BPF_PSEUDO_FUNC		4

/* when bpf_call->src_reg == BPF_PSEUDO_CALL, bpf_call->imm == pc-relative
 * offset to another bpf function
 */
#घोषणा BPF_PSEUDO_CALL		1
/* when bpf_call->src_reg == BPF_PSEUDO_KFUNC_CALL,
 * bpf_call->imm == btf_id of a BTF_KIND_FUNC in the running kernel
 */
#घोषणा BPF_PSEUDO_KFUNC_CALL	2

/* flags क्रम BPF_MAP_UPDATE_ELEM command */
क्रमागत अणु
	BPF_ANY		= 0, /* create new element or update existing */
	BPF_NOEXIST	= 1, /* create new element अगर it didn't exist */
	BPF_EXIST	= 2, /* update existing element */
	BPF_F_LOCK	= 4, /* spin_lock-ed map_lookup/map_update */
पूर्ण;

/* flags क्रम BPF_MAP_CREATE command */
क्रमागत अणु
	BPF_F_NO_PREALLOC	= (1U << 0),
/* Instead of having one common LRU list in the
 * BPF_MAP_TYPE_LRU_[PERCPU_]HASH map, use a percpu LRU list
 * which can scale and perक्रमm better.
 * Note, the LRU nodes (including मुक्त nodes) cannot be moved
 * across dअगरferent LRU lists.
 */
	BPF_F_NO_COMMON_LRU	= (1U << 1),
/* Specअगरy numa node during map creation */
	BPF_F_NUMA_NODE		= (1U << 2),

/* Flags क्रम accessing BPF object from syscall side. */
	BPF_F_RDONLY		= (1U << 3),
	BPF_F_WRONLY		= (1U << 4),

/* Flag क्रम stack_map, store build_id+offset instead of poपूर्णांकer */
	BPF_F_STACK_BUILD_ID	= (1U << 5),

/* Zero-initialize hash function seed. This should only be used क्रम testing. */
	BPF_F_ZERO_SEED		= (1U << 6),

/* Flags क्रम accessing BPF object from program side. */
	BPF_F_RDONLY_PROG	= (1U << 7),
	BPF_F_WRONLY_PROG	= (1U << 8),

/* Clone map from listener क्रम newly accepted socket */
	BPF_F_CLONE		= (1U << 9),

/* Enable memory-mapping BPF map */
	BPF_F_MMAPABLE		= (1U << 10),

/* Share perf_event among processes */
	BPF_F_PRESERVE_ELEMS	= (1U << 11),

/* Create a map that is suitable to be an inner map with dynamic max entries */
	BPF_F_INNER_MAP		= (1U << 12),
पूर्ण;

/* Flags क्रम BPF_PROG_QUERY. */

/* Query effective (directly attached + inherited from ancestor cgroups)
 * programs that will be executed क्रम events within a cgroup.
 * attach_flags with this flag are वापसed only क्रम directly attached programs.
 */
#घोषणा BPF_F_QUERY_EFFECTIVE	(1U << 0)

/* Flags क्रम BPF_PROG_TEST_RUN */

/* If set, run the test on the cpu specअगरied by bpf_attr.test.cpu */
#घोषणा BPF_F_TEST_RUN_ON_CPU	(1U << 0)

/* type क्रम BPF_ENABLE_STATS */
क्रमागत bpf_stats_type अणु
	/* enabled run_समय_ns and run_cnt */
	BPF_STATS_RUN_TIME = 0,
पूर्ण;

क्रमागत bpf_stack_build_id_status अणु
	/* user space need an empty entry to identअगरy end of a trace */
	BPF_STACK_BUILD_ID_EMPTY = 0,
	/* with valid build_id and offset */
	BPF_STACK_BUILD_ID_VALID = 1,
	/* couldn't get build_id, fallback to ip */
	BPF_STACK_BUILD_ID_IP = 2,
पूर्ण;

#घोषणा BPF_BUILD_ID_SIZE 20
काष्ठा bpf_stack_build_id अणु
	__s32		status;
	अचिन्हित अक्षर	build_id[BPF_BUILD_ID_SIZE];
	जोड़ अणु
		__u64	offset;
		__u64	ip;
	पूर्ण;
पूर्ण;

#घोषणा BPF_OBJ_NAME_LEN 16U

जोड़ bpf_attr अणु
	काष्ठा अणु /* anonymous काष्ठा used by BPF_MAP_CREATE command */
		__u32	map_type;	/* one of क्रमागत bpf_map_type */
		__u32	key_size;	/* size of key in bytes */
		__u32	value_size;	/* size of value in bytes */
		__u32	max_entries;	/* max number of entries in a map */
		__u32	map_flags;	/* BPF_MAP_CREATE related
					 * flags defined above.
					 */
		__u32	inner_map_fd;	/* fd poपूर्णांकing to the inner map */
		__u32	numa_node;	/* numa node (effective only अगर
					 * BPF_F_NUMA_NODE is set).
					 */
		अक्षर	map_name[BPF_OBJ_NAME_LEN];
		__u32	map_अगरindex;	/* अगरindex of netdev to create on */
		__u32	btf_fd;		/* fd poपूर्णांकing to a BTF type data */
		__u32	btf_key_type_id;	/* BTF type_id of the key */
		__u32	btf_value_type_id;	/* BTF type_id of the value */
		__u32	btf_vmlinux_value_type_id;/* BTF type_id of a kernel-
						   * काष्ठा stored as the
						   * map value
						   */
	पूर्ण;

	काष्ठा अणु /* anonymous काष्ठा used by BPF_MAP_*_ELEM commands */
		__u32		map_fd;
		__aligned_u64	key;
		जोड़ अणु
			__aligned_u64 value;
			__aligned_u64 next_key;
		पूर्ण;
		__u64		flags;
	पूर्ण;

	काष्ठा अणु /* काष्ठा used by BPF_MAP_*_BATCH commands */
		__aligned_u64	in_batch;	/* start batch,
						 * शून्य to start from beginning
						 */
		__aligned_u64	out_batch;	/* output: next start batch */
		__aligned_u64	keys;
		__aligned_u64	values;
		__u32		count;		/* input/output:
						 * input: # of key/value
						 * elements
						 * output: # of filled elements
						 */
		__u32		map_fd;
		__u64		elem_flags;
		__u64		flags;
	पूर्ण batch;

	काष्ठा अणु /* anonymous काष्ठा used by BPF_PROG_LOAD command */
		__u32		prog_type;	/* one of क्रमागत bpf_prog_type */
		__u32		insn_cnt;
		__aligned_u64	insns;
		__aligned_u64	license;
		__u32		log_level;	/* verbosity level of verअगरier */
		__u32		log_size;	/* size of user buffer */
		__aligned_u64	log_buf;	/* user supplied buffer */
		__u32		kern_version;	/* not used */
		__u32		prog_flags;
		अक्षर		prog_name[BPF_OBJ_NAME_LEN];
		__u32		prog_अगरindex;	/* अगरindex of netdev to prep क्रम */
		/* For some prog types expected attach type must be known at
		 * load समय to verअगरy attach type specअगरic parts of prog
		 * (context accesses, allowed helpers, etc).
		 */
		__u32		expected_attach_type;
		__u32		prog_btf_fd;	/* fd poपूर्णांकing to BTF type data */
		__u32		func_info_rec_size;	/* userspace bpf_func_info size */
		__aligned_u64	func_info;	/* func info */
		__u32		func_info_cnt;	/* number of bpf_func_info records */
		__u32		line_info_rec_size;	/* userspace bpf_line_info size */
		__aligned_u64	line_info;	/* line info */
		__u32		line_info_cnt;	/* number of bpf_line_info records */
		__u32		attach_btf_id;	/* in-kernel BTF type id to attach to */
		जोड़ अणु
			/* valid prog_fd to attach to bpf prog */
			__u32		attach_prog_fd;
			/* or valid module BTF object fd or 0 to attach to vmlinux */
			__u32		attach_btf_obj_fd;
		पूर्ण;
	पूर्ण;

	काष्ठा अणु /* anonymous काष्ठा used by BPF_OBJ_* commands */
		__aligned_u64	pathname;
		__u32		bpf_fd;
		__u32		file_flags;
	पूर्ण;

	काष्ठा अणु /* anonymous काष्ठा used by BPF_PROG_ATTACH/DETACH commands */
		__u32		target_fd;	/* container object to attach to */
		__u32		attach_bpf_fd;	/* eBPF program to attach */
		__u32		attach_type;
		__u32		attach_flags;
		__u32		replace_bpf_fd;	/* previously attached eBPF
						 * program to replace अगर
						 * BPF_F_REPLACE is used
						 */
	पूर्ण;

	काष्ठा अणु /* anonymous काष्ठा used by BPF_PROG_TEST_RUN command */
		__u32		prog_fd;
		__u32		retval;
		__u32		data_size_in;	/* input: len of data_in */
		__u32		data_size_out;	/* input/output: len of data_out
						 *   वापसs ENOSPC अगर data_out
						 *   is too small.
						 */
		__aligned_u64	data_in;
		__aligned_u64	data_out;
		__u32		repeat;
		__u32		duration;
		__u32		ctx_size_in;	/* input: len of ctx_in */
		__u32		ctx_size_out;	/* input/output: len of ctx_out
						 *   वापसs ENOSPC अगर ctx_out
						 *   is too small.
						 */
		__aligned_u64	ctx_in;
		__aligned_u64	ctx_out;
		__u32		flags;
		__u32		cpu;
	पूर्ण test;

	काष्ठा अणु /* anonymous काष्ठा used by BPF_*_GET_*_ID */
		जोड़ अणु
			__u32		start_id;
			__u32		prog_id;
			__u32		map_id;
			__u32		btf_id;
			__u32		link_id;
		पूर्ण;
		__u32		next_id;
		__u32		खोलो_flags;
	पूर्ण;

	काष्ठा अणु /* anonymous काष्ठा used by BPF_OBJ_GET_INFO_BY_FD */
		__u32		bpf_fd;
		__u32		info_len;
		__aligned_u64	info;
	पूर्ण info;

	काष्ठा अणु /* anonymous काष्ठा used by BPF_PROG_QUERY command */
		__u32		target_fd;	/* container object to query */
		__u32		attach_type;
		__u32		query_flags;
		__u32		attach_flags;
		__aligned_u64	prog_ids;
		__u32		prog_cnt;
	पूर्ण query;

	काष्ठा अणु /* anonymous काष्ठा used by BPF_RAW_TRACEPOINT_OPEN command */
		__u64 name;
		__u32 prog_fd;
	पूर्ण raw_tracepoपूर्णांक;

	काष्ठा अणु /* anonymous काष्ठा क्रम BPF_BTF_LOAD */
		__aligned_u64	btf;
		__aligned_u64	btf_log_buf;
		__u32		btf_size;
		__u32		btf_log_size;
		__u32		btf_log_level;
	पूर्ण;

	काष्ठा अणु
		__u32		pid;		/* input: pid */
		__u32		fd;		/* input: fd */
		__u32		flags;		/* input: flags */
		__u32		buf_len;	/* input/output: buf len */
		__aligned_u64	buf;		/* input/output:
						 *   tp_name क्रम tracepoपूर्णांक
						 *   symbol क्रम kprobe
						 *   filename क्रम uprobe
						 */
		__u32		prog_id;	/* output: prod_id */
		__u32		fd_type;	/* output: BPF_FD_TYPE_* */
		__u64		probe_offset;	/* output: probe_offset */
		__u64		probe_addr;	/* output: probe_addr */
	पूर्ण task_fd_query;

	काष्ठा अणु /* काष्ठा used by BPF_LINK_CREATE command */
		__u32		prog_fd;	/* eBPF program to attach */
		जोड़ अणु
			__u32		target_fd;	/* object to attach to */
			__u32		target_अगरindex; /* target अगरindex */
		पूर्ण;
		__u32		attach_type;	/* attach type */
		__u32		flags;		/* extra flags */
		जोड़ अणु
			__u32		target_btf_id;	/* btf_id of target to attach to */
			काष्ठा अणु
				__aligned_u64	iter_info;	/* extra bpf_iter_link_info */
				__u32		iter_info_len;	/* iter_info length */
			पूर्ण;
		पूर्ण;
	पूर्ण link_create;

	काष्ठा अणु /* काष्ठा used by BPF_LINK_UPDATE command */
		__u32		link_fd;	/* link fd */
		/* new program fd to update link with */
		__u32		new_prog_fd;
		__u32		flags;		/* extra flags */
		/* expected link's program fd; is specअगरied only अगर
		 * BPF_F_REPLACE flag is set in flags */
		__u32		old_prog_fd;
	पूर्ण link_update;

	काष्ठा अणु
		__u32		link_fd;
	पूर्ण link_detach;

	काष्ठा अणु /* काष्ठा used by BPF_ENABLE_STATS command */
		__u32		type;
	पूर्ण enable_stats;

	काष्ठा अणु /* काष्ठा used by BPF_ITER_CREATE command */
		__u32		link_fd;
		__u32		flags;
	पूर्ण iter_create;

	काष्ठा अणु /* काष्ठा used by BPF_PROG_BIND_MAP command */
		__u32		prog_fd;
		__u32		map_fd;
		__u32		flags;		/* extra flags */
	पूर्ण prog_bind_map;

पूर्ण __attribute__((aligned(8)));

/* The description below is an attempt at providing करोcumentation to eBPF
 * developers about the multiple available eBPF helper functions. It can be
 * parsed and used to produce a manual page. The workflow is the following,
 * and requires the rst2man utility:
 *
 *     $ ./scripts/bpf_करोc.py \
 *             --filename include/uapi/linux/bpf.h > /पंचांगp/bpf-helpers.rst
 *     $ rst2man /पंचांगp/bpf-helpers.rst > /पंचांगp/bpf-helpers.7
 *     $ man /पंचांगp/bpf-helpers.7
 *
 * Note that in order to produce this बाह्यal करोcumentation, some RST
 * क्रमmatting is used in the descriptions to get "bold" and "italics" in
 * manual pages. Also note that the few trailing white spaces are
 * पूर्णांकentional, removing them would अवरोध paragraphs क्रम rst2man.
 *
 * Start of BPF helper function descriptions:
 *
 * व्योम *bpf_map_lookup_elem(काष्ठा bpf_map *map, स्थिर व्योम *key)
 * 	Description
 * 		Perक्रमm a lookup in *map* क्रम an entry associated to *key*.
 * 	Return
 * 		Map value associated to *key*, or **शून्य** अगर no entry was
 * 		found.
 *
 * दीर्घ bpf_map_update_elem(काष्ठा bpf_map *map, स्थिर व्योम *key, स्थिर व्योम *value, u64 flags)
 * 	Description
 * 		Add or update the value of the entry associated to *key* in
 * 		*map* with *value*. *flags* is one of:
 *
 * 		**BPF_NOEXIST**
 * 			The entry क्रम *key* must not exist in the map.
 * 		**BPF_EXIST**
 * 			The entry क्रम *key* must alपढ़ोy exist in the map.
 * 		**BPF_ANY**
 * 			No condition on the existence of the entry क्रम *key*.
 *
 * 		Flag value **BPF_NOEXIST** cannot be used क्रम maps of types
 * 		**BPF_MAP_TYPE_ARRAY** or **BPF_MAP_TYPE_PERCPU_ARRAY**  (all
 * 		elements always exist), the helper would वापस an error.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_map_delete_elem(काष्ठा bpf_map *map, स्थिर व्योम *key)
 * 	Description
 * 		Delete entry with *key* from *map*.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_probe_पढ़ो(व्योम *dst, u32 size, स्थिर व्योम *unsafe_ptr)
 * 	Description
 * 		For tracing programs, safely attempt to पढ़ो *size* bytes from
 * 		kernel space address *unsafe_ptr* and store the data in *dst*.
 *
 * 		Generally, use **bpf_probe_पढ़ो_user**\ () or
 * 		**bpf_probe_पढ़ो_kernel**\ () instead.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * u64 bpf_kसमय_get_ns(व्योम)
 * 	Description
 * 		Return the समय elapsed since प्रणाली boot, in nanoseconds.
 * 		Does not include समय the प्रणाली was suspended.
 * 		See: **घड़ी_समय_लो**\ (**CLOCK_MONOTONIC**)
 * 	Return
 * 		Current *kसमय*.
 *
 * दीर्घ bpf_trace_prपूर्णांकk(स्थिर अक्षर *fmt, u32 fmt_size, ...)
 * 	Description
 * 		This helper is a "printk()-like" facility क्रम debugging. It
 * 		prपूर्णांकs a message defined by क्रमmat *fmt* (of size *fmt_size*)
 * 		to file *\/sys/kernel/debug/tracing/trace* from DebugFS, अगर
 * 		available. It can take up to three additional **u64**
 * 		arguments (as an eBPF helpers, the total number of arguments is
 * 		limited to five).
 *
 * 		Each समय the helper is called, it appends a line to the trace.
 * 		Lines are discarded जबतक *\/sys/kernel/debug/tracing/trace* is
 * 		खोलो, use *\/sys/kernel/debug/tracing/trace_pipe* to aव्योम this.
 * 		The क्रमmat of the trace is customizable, and the exact output
 * 		one will get depends on the options set in
 * 		*\/sys/kernel/debug/tracing/trace_options* (see also the
 * 		*README* file under the same directory). However, it usually
 * 		शेषs to something like:
 *
 * 		::
 *
 * 			telnet-470   [001] .N.. 419421.045894: 0x00000001: <क्रमmatted msg>
 *
 * 		In the above:
 *
 * 			* ``telnet`` is the name of the current task.
 * 			* ``470`` is the PID of the current task.
 * 			* ``001`` is the CPU number on which the task is
 * 			  running.
 * 			* In ``.N..``, each अक्षरacter refers to a set of
 * 			  options (whether irqs are enabled, scheduling
 * 			  options, whether hard/softirqs are running, level of
 * 			  preempt_disabled respectively). **N** means that
 * 			  **TIF_NEED_RESCHED** and **PREEMPT_NEED_RESCHED**
 * 			  are set.
 * 			* ``419421.045894`` is a बारtamp.
 * 			* ``0x00000001`` is a fake value used by BPF क्रम the
 * 			  inकाष्ठाion poपूर्णांकer रेजिस्टर.
 * 			* ``<क्रमmatted msg>`` is the message क्रमmatted with
 * 			  *fmt*.
 *
 * 		The conversion specअगरiers supported by *fmt* are similar, but
 * 		more limited than क्रम prपूर्णांकk(). They are **%d**, **%i**,
 * 		**%u**, **%x**, **%ld**, **%li**, **%lu**, **%lx**, **%lld**,
 * 		**%lli**, **%llu**, **%llx**, **%p**, **%s**. No modअगरier (size
 * 		of field, padding with zeroes, etc.) is available, and the
 * 		helper will वापस **-EINVAL** (but prपूर्णांक nothing) अगर it
 * 		encounters an unknown specअगरier.
 *
 * 		Also, note that **bpf_trace_prपूर्णांकk**\ () is slow, and should
 * 		only be used क्रम debugging purposes. For this reason, a notice
 * 		block (spanning several lines) is prपूर्णांकed to kernel logs and
 * 		states that the helper should not be used "for production use"
 * 		the first समय this helper is used (or more precisely, when
 * 		**trace_prपूर्णांकk**\ () buffers are allocated). For passing values
 * 		to user space, perf events should be preferred.
 * 	Return
 * 		The number of bytes written to the buffer, or a negative error
 * 		in हाल of failure.
 *
 * u32 bpf_get_pअक्रमom_u32(व्योम)
 * 	Description
 * 		Get a pseuकरो-अक्रमom number.
 *
 * 		From a security poपूर्णांक of view, this helper uses its own
 * 		pseuकरो-अक्रमom पूर्णांकernal state, and cannot be used to infer the
 * 		seed of other अक्रमom functions in the kernel. However, it is
 * 		essential to note that the generator used by the helper is not
 * 		cryptographically secure.
 * 	Return
 * 		A अक्रमom 32-bit अचिन्हित value.
 *
 * u32 bpf_get_smp_processor_id(व्योम)
 * 	Description
 * 		Get the SMP (symmetric multiprocessing) processor id. Note that
 * 		all programs run with preemption disabled, which means that the
 * 		SMP processor id is stable during all the execution of the
 * 		program.
 * 	Return
 * 		The SMP id of the processor running the program.
 *
 * दीर्घ bpf_skb_store_bytes(काष्ठा sk_buff *skb, u32 offset, स्थिर व्योम *from, u32 len, u64 flags)
 * 	Description
 * 		Store *len* bytes from address *from* पूर्णांकo the packet
 * 		associated to *skb*, at *offset*. *flags* are a combination of
 * 		**BPF_F_RECOMPUTE_CSUM** (स्वतःmatically recompute the
 * 		checksum क्रम the packet after storing the bytes) and
 * 		**BPF_F_INVALIDATE_HASH** (set *skb*\ **->hash**, *skb*\
 * 		**->swhash** and *skb*\ **->l4hash** to 0).
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_l3_csum_replace(काष्ठा sk_buff *skb, u32 offset, u64 from, u64 to, u64 size)
 * 	Description
 * 		Recompute the layer 3 (e.g. IP) checksum क्रम the packet
 * 		associated to *skb*. Computation is incremental, so the helper
 * 		must know the क्रमmer value of the header field that was
 * 		modअगरied (*from*), the new value of this field (*to*), and the
 * 		number of bytes (2 or 4) क्रम this field, stored in *size*.
 * 		Alternatively, it is possible to store the dअगरference between
 * 		the previous and the new values of the header field in *to*, by
 * 		setting *from* and *size* to 0. For both methods, *offset*
 * 		indicates the location of the IP checksum within the packet.
 *
 * 		This helper works in combination with **bpf_csum_dअगरf**\ (),
 * 		which करोes not update the checksum in-place, but offers more
 * 		flexibility and can handle sizes larger than 2 or 4 क्रम the
 * 		checksum to update.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_l4_csum_replace(काष्ठा sk_buff *skb, u32 offset, u64 from, u64 to, u64 flags)
 * 	Description
 * 		Recompute the layer 4 (e.g. TCP, UDP or ICMP) checksum क्रम the
 * 		packet associated to *skb*. Computation is incremental, so the
 * 		helper must know the क्रमmer value of the header field that was
 * 		modअगरied (*from*), the new value of this field (*to*), and the
 * 		number of bytes (2 or 4) क्रम this field, stored on the lowest
 * 		four bits of *flags*. Alternatively, it is possible to store
 * 		the dअगरference between the previous and the new values of the
 * 		header field in *to*, by setting *from* and the four lowest
 * 		bits of *flags* to 0. For both methods, *offset* indicates the
 * 		location of the IP checksum within the packet. In addition to
 * 		the size of the field, *flags* can be added (bitwise OR) actual
 * 		flags. With **BPF_F_MARK_MANGLED_0**, a null checksum is left
 * 		untouched (unless **BPF_F_MARK_ENFORCE** is added as well), and
 * 		क्रम updates resulting in a null checksum the value is set to
 * 		**CSUM_MANGLED_0** instead. Flag **BPF_F_PSEUDO_HDR** indicates
 * 		the checksum is to be computed against a pseuकरो-header.
 *
 * 		This helper works in combination with **bpf_csum_dअगरf**\ (),
 * 		which करोes not update the checksum in-place, but offers more
 * 		flexibility and can handle sizes larger than 2 or 4 क्रम the
 * 		checksum to update.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_tail_call(व्योम *ctx, काष्ठा bpf_map *prog_array_map, u32 index)
 * 	Description
 * 		This special helper is used to trigger a "tail call", or in
 * 		other words, to jump पूर्णांकo another eBPF program. The same stack
 * 		frame is used (but values on stack and in रेजिस्टरs क्रम the
 * 		caller are not accessible to the callee). This mechanism allows
 * 		क्रम program chaining, either क्रम raising the maximum number of
 * 		available eBPF inकाष्ठाions, or to execute given programs in
 * 		conditional blocks. For security reasons, there is an upper
 * 		limit to the number of successive tail calls that can be
 * 		perक्रमmed.
 *
 * 		Upon call of this helper, the program attempts to jump पूर्णांकo a
 * 		program referenced at index *index* in *prog_array_map*, a
 * 		special map of type **BPF_MAP_TYPE_PROG_ARRAY**, and passes
 * 		*ctx*, a poपूर्णांकer to the context.
 *
 * 		If the call succeeds, the kernel immediately runs the first
 * 		inकाष्ठाion of the new program. This is not a function call,
 * 		and it never वापसs to the previous program. If the call
 * 		fails, then the helper has no effect, and the caller जारीs
 * 		to run its subsequent inकाष्ठाions. A call can fail अगर the
 * 		destination program क्रम the jump करोes not exist (i.e. *index*
 * 		is superior to the number of entries in *prog_array_map*), or
 * 		अगर the maximum number of tail calls has been reached क्रम this
 * 		chain of programs. This limit is defined in the kernel by the
 * 		macro **MAX_TAIL_CALL_CNT** (not accessible to user space),
 * 		which is currently set to 32.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_clone_redirect(काष्ठा sk_buff *skb, u32 अगरindex, u64 flags)
 * 	Description
 * 		Clone and redirect the packet associated to *skb* to another
 * 		net device of index *अगरindex*. Both ingress and egress
 * 		पूर्णांकerfaces can be used क्रम redirection. The **BPF_F_INGRESS**
 * 		value in *flags* is used to make the distinction (ingress path
 * 		is selected अगर the flag is present, egress path otherwise).
 * 		This is the only flag supported क्रम now.
 *
 * 		In comparison with **bpf_redirect**\ () helper,
 * 		**bpf_clone_redirect**\ () has the associated cost of
 * 		duplicating the packet buffer, but this can be executed out of
 * 		the eBPF program. Conversely, **bpf_redirect**\ () is more
 * 		efficient, but it is handled through an action code where the
 * 		redirection happens only after the eBPF program has वापसed.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * u64 bpf_get_current_pid_tgid(व्योम)
 * 	Return
 * 		A 64-bit पूर्णांकeger containing the current tgid and pid, and
 * 		created as such:
 * 		*current_task*\ **->tgid << 32 \|**
 * 		*current_task*\ **->pid**.
 *
 * u64 bpf_get_current_uid_gid(व्योम)
 * 	Return
 * 		A 64-bit पूर्णांकeger containing the current GID and UID, and
 * 		created as such: *current_gid* **<< 32 \|** *current_uid*.
 *
 * दीर्घ bpf_get_current_comm(व्योम *buf, u32 size_of_buf)
 * 	Description
 * 		Copy the **comm** attribute of the current task पूर्णांकo *buf* of
 * 		*size_of_buf*. The **comm** attribute contains the name of
 * 		the executable (excluding the path) क्रम the current task. The
 * 		*size_of_buf* must be strictly positive. On success, the
 * 		helper makes sure that the *buf* is NUL-terminated. On failure,
 * 		it is filled with zeroes.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * u32 bpf_get_cgroup_classid(काष्ठा sk_buff *skb)
 * 	Description
 * 		Retrieve the classid क्रम the current task, i.e. क्रम the net_cls
 * 		cgroup to which *skb* beदीर्घs.
 *
 * 		This helper can be used on TC egress path, but not on ingress.
 *
 * 		The net_cls cgroup provides an पूर्णांकerface to tag network packets
 * 		based on a user-provided identअगरier क्रम all traffic coming from
 * 		the tasks beदीर्घing to the related cgroup. See also the related
 * 		kernel करोcumentation, available from the Linux sources in file
 * 		*Documentation/admin-guide/cgroup-v1/net_cls.rst*.
 *
 * 		The Linux kernel has two versions क्रम cgroups: there are
 * 		cgroups v1 and cgroups v2. Both are available to users, who can
 * 		use a mixture of them, but note that the net_cls cgroup is क्रम
 * 		cgroup v1 only. This makes it incompatible with BPF programs
 * 		run on cgroups, which is a cgroup-v2-only feature (a socket can
 * 		only hold data क्रम one version of cgroups at a समय).
 *
 * 		This helper is only available is the kernel was compiled with
 * 		the **CONFIG_CGROUP_NET_CLASSID** configuration option set to
 * 		"**y**" or to "**m**".
 * 	Return
 * 		The classid, or 0 क्रम the शेष unconfigured classid.
 *
 * दीर्घ bpf_skb_vlan_push(काष्ठा sk_buff *skb, __be16 vlan_proto, u16 vlan_tci)
 * 	Description
 * 		Push a *vlan_tci* (VLAN tag control inक्रमmation) of protocol
 * 		*vlan_proto* to the packet associated to *skb*, then update
 * 		the checksum. Note that अगर *vlan_proto* is dअगरferent from
 * 		**ETH_P_8021Q** and **ETH_P_8021AD**, it is considered to
 * 		be **ETH_P_8021Q**.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_skb_vlan_pop(काष्ठा sk_buff *skb)
 * 	Description
 * 		Pop a VLAN header from the packet associated to *skb*.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_skb_get_tunnel_key(काष्ठा sk_buff *skb, काष्ठा bpf_tunnel_key *key, u32 size, u64 flags)
 * 	Description
 * 		Get tunnel metadata. This helper takes a poपूर्णांकer *key* to an
 * 		empty **काष्ठा bpf_tunnel_key** of **size**, that will be
 * 		filled with tunnel metadata क्रम the packet associated to *skb*.
 * 		The *flags* can be set to **BPF_F_TUNINFO_IPV6**, which
 * 		indicates that the tunnel is based on IPv6 protocol instead of
 * 		IPv4.
 *
 * 		The **काष्ठा bpf_tunnel_key** is an object that generalizes the
 * 		principal parameters used by various tunneling protocols पूर्णांकo a
 * 		single काष्ठा. This way, it can be used to easily make a
 * 		decision based on the contents of the encapsulation header,
 * 		"summarized" in this काष्ठा. In particular, it holds the IP
 * 		address of the remote end (IPv4 or IPv6, depending on the हाल)
 * 		in *key*\ **->remote_ipv4** or *key*\ **->remote_ipv6**. Also,
 * 		this काष्ठा exposes the *key*\ **->tunnel_id**, which is
 * 		generally mapped to a VNI (Virtual Network Identअगरier), making
 * 		it programmable together with the **bpf_skb_set_tunnel_key**\
 * 		() helper.
 *
 * 		Let's imagine that the following code is part of a program
 * 		attached to the TC ingress पूर्णांकerface, on one end of a GRE
 * 		tunnel, and is supposed to filter out all messages coming from
 * 		remote ends with IPv4 address other than 10.0.0.1:
 *
 * 		::
 *
 * 			पूर्णांक ret;
 * 			काष्ठा bpf_tunnel_key key = अणुपूर्ण;
 *
 * 			ret = bpf_skb_get_tunnel_key(skb, &key, माप(key), 0);
 * 			अगर (ret < 0)
 * 				वापस TC_ACT_SHOT;	// drop packet
 *
 * 			अगर (key.remote_ipv4 != 0x0a000001)
 * 				वापस TC_ACT_SHOT;	// drop packet
 *
 * 			वापस TC_ACT_OK;		// accept packet
 *
 * 		This पूर्णांकerface can also be used with all encapsulation devices
 * 		that can operate in "collect metadata" mode: instead of having
 * 		one network device per specअगरic configuration, the "collect
 * 		metadata" mode only requires a single device where the
 * 		configuration can be extracted from this helper.
 *
 * 		This can be used together with various tunnels such as VXLan,
 * 		Geneve, GRE or IP in IP (IPIP).
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_skb_set_tunnel_key(काष्ठा sk_buff *skb, काष्ठा bpf_tunnel_key *key, u32 size, u64 flags)
 * 	Description
 * 		Populate tunnel metadata क्रम packet associated to *skb.* The
 * 		tunnel metadata is set to the contents of *key*, of *size*. The
 * 		*flags* can be set to a combination of the following values:
 *
 * 		**BPF_F_TUNINFO_IPV6**
 * 			Indicate that the tunnel is based on IPv6 protocol
 * 			instead of IPv4.
 * 		**BPF_F_ZERO_CSUM_TX**
 * 			For IPv4 packets, add a flag to tunnel metadata
 * 			indicating that checksum computation should be skipped
 * 			and checksum set to zeroes.
 * 		**BPF_F_DONT_FRAGMENT**
 * 			Add a flag to tunnel metadata indicating that the
 * 			packet should not be fragmented.
 * 		**BPF_F_SEQ_NUMBER**
 * 			Add a flag to tunnel metadata indicating that a
 * 			sequence number should be added to tunnel header beक्रमe
 * 			sending the packet. This flag was added क्रम GRE
 * 			encapsulation, but might be used with other protocols
 * 			as well in the future.
 *
 * 		Here is a typical usage on the transmit path:
 *
 * 		::
 *
 * 			काष्ठा bpf_tunnel_key key;
 * 			     populate key ...
 * 			bpf_skb_set_tunnel_key(skb, &key, माप(key), 0);
 * 			bpf_clone_redirect(skb, vxlan_dev_अगरindex, 0);
 *
 * 		See also the description of the **bpf_skb_get_tunnel_key**\ ()
 * 		helper क्रम additional inक्रमmation.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * u64 bpf_perf_event_पढ़ो(काष्ठा bpf_map *map, u64 flags)
 * 	Description
 * 		Read the value of a perf event counter. This helper relies on a
 * 		*map* of type **BPF_MAP_TYPE_PERF_EVENT_ARRAY**. The nature of
 * 		the perf event counter is selected when *map* is updated with
 * 		perf event file descriptors. The *map* is an array whose size
 * 		is the number of available CPUs, and each cell contains a value
 * 		relative to one CPU. The value to retrieve is indicated by
 * 		*flags*, that contains the index of the CPU to look up, masked
 * 		with **BPF_F_INDEX_MASK**. Alternatively, *flags* can be set to
 * 		**BPF_F_CURRENT_CPU** to indicate that the value क्रम the
 * 		current CPU should be retrieved.
 *
 * 		Note that beक्रमe Linux 4.13, only hardware perf event can be
 * 		retrieved.
 *
 * 		Also, be aware that the newer helper
 * 		**bpf_perf_event_पढ़ो_value**\ () is recommended over
 * 		**bpf_perf_event_पढ़ो**\ () in general. The latter has some ABI
 * 		quirks where error and counter value are used as a वापस code
 * 		(which is wrong to करो since ranges may overlap). This issue is
 * 		fixed with **bpf_perf_event_पढ़ो_value**\ (), which at the same
 * 		समय provides more features over the **bpf_perf_event_पढ़ो**\
 * 		() पूर्णांकerface. Please refer to the description of
 * 		**bpf_perf_event_पढ़ो_value**\ () क्रम details.
 * 	Return
 * 		The value of the perf event counter पढ़ो from the map, or a
 * 		negative error code in हाल of failure.
 *
 * दीर्घ bpf_redirect(u32 अगरindex, u64 flags)
 * 	Description
 * 		Redirect the packet to another net device of index *अगरindex*.
 * 		This helper is somewhat similar to **bpf_clone_redirect**\
 * 		(), except that the packet is not cloned, which provides
 * 		increased perक्रमmance.
 *
 * 		Except क्रम XDP, both ingress and egress पूर्णांकerfaces can be used
 * 		क्रम redirection. The **BPF_F_INGRESS** value in *flags* is used
 * 		to make the distinction (ingress path is selected अगर the flag
 * 		is present, egress path otherwise). Currently, XDP only
 * 		supports redirection to the egress पूर्णांकerface, and accepts no
 * 		flag at all.
 *
 * 		The same effect can also be attained with the more generic
 * 		**bpf_redirect_map**\ (), which uses a BPF map to store the
 * 		redirect target instead of providing it directly to the helper.
 * 	Return
 * 		For XDP, the helper वापसs **XDP_REसूचीECT** on success or
 * 		**XDP_ABORTED** on error. For other program types, the values
 * 		are **TC_ACT_REसूचीECT** on success or **TC_ACT_SHOT** on
 * 		error.
 *
 * u32 bpf_get_route_realm(काष्ठा sk_buff *skb)
 * 	Description
 * 		Retrieve the realm or the route, that is to say the
 * 		**tclassid** field of the destination क्रम the *skb*. The
 * 		identअगरier retrieved is a user-provided tag, similar to the
 * 		one used with the net_cls cgroup (see description क्रम
 * 		**bpf_get_cgroup_classid**\ () helper), but here this tag is
 * 		held by a route (a destination entry), not by a task.
 *
 * 		Retrieving this identअगरier works with the clsact TC egress hook
 * 		(see also **tc-bpf(8)**), or alternatively on conventional
 * 		classful egress qdiscs, but not on TC ingress path. In हाल of
 * 		clsact TC egress hook, this has the advantage that, पूर्णांकernally,
 * 		the destination entry has not been dropped yet in the transmit
 * 		path. Thereक्रमe, the destination entry करोes not need to be
 * 		artअगरicially held via **netअगर_keep_dst**\ () क्रम a classful
 * 		qdisc until the *skb* is मुक्तd.
 *
 * 		This helper is available only अगर the kernel was compiled with
 * 		**CONFIG_IP_ROUTE_CLASSID** configuration option.
 * 	Return
 * 		The realm of the route क्रम the packet associated to *skb*, or 0
 * 		अगर none was found.
 *
 * दीर्घ bpf_perf_event_output(व्योम *ctx, काष्ठा bpf_map *map, u64 flags, व्योम *data, u64 size)
 * 	Description
 * 		Write raw *data* blob पूर्णांकo a special BPF perf event held by
 * 		*map* of type **BPF_MAP_TYPE_PERF_EVENT_ARRAY**. This perf
 * 		event must have the following attributes: **PERF_SAMPLE_RAW**
 * 		as **sample_type**, **PERF_TYPE_SOFTWARE** as **type**, and
 * 		**PERF_COUNT_SW_BPF_OUTPUT** as **config**.
 *
 * 		The *flags* are used to indicate the index in *map* क्रम which
 * 		the value must be put, masked with **BPF_F_INDEX_MASK**.
 * 		Alternatively, *flags* can be set to **BPF_F_CURRENT_CPU**
 * 		to indicate that the index of the current CPU core should be
 * 		used.
 *
 * 		The value to ग_लिखो, of *size*, is passed through eBPF stack and
 * 		poपूर्णांकed by *data*.
 *
 * 		The context of the program *ctx* needs also be passed to the
 * 		helper.
 *
 * 		On user space, a program willing to पढ़ो the values needs to
 * 		call **perf_event_खोलो**\ () on the perf event (either क्रम
 * 		one or क्रम all CPUs) and to store the file descriptor पूर्णांकo the
 * 		*map*. This must be करोne beक्रमe the eBPF program can send data
 * 		पूर्णांकo it. An example is available in file
 * 		*samples/bpf/trace_output_user.c* in the Linux kernel source
 * 		tree (the eBPF program counterpart is in
 * 		*samples/bpf/trace_output_kern.c*).
 *
 * 		**bpf_perf_event_output**\ () achieves better perक्रमmance
 * 		than **bpf_trace_prपूर्णांकk**\ () क्रम sharing data with user
 * 		space, and is much better suitable क्रम streaming data from eBPF
 * 		programs.
 *
 * 		Note that this helper is not restricted to tracing use हालs
 * 		and can be used with programs attached to TC or XDP as well,
 * 		where it allows क्रम passing data to user space listeners. Data
 * 		can be:
 *
 * 		* Only custom काष्ठाs,
 * 		* Only the packet payload, or
 * 		* A combination of both.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_skb_load_bytes(स्थिर व्योम *skb, u32 offset, व्योम *to, u32 len)
 * 	Description
 * 		This helper was provided as an easy way to load data from a
 * 		packet. It can be used to load *len* bytes from *offset* from
 * 		the packet associated to *skb*, पूर्णांकo the buffer poपूर्णांकed by
 * 		*to*.
 *
 * 		Since Linux 4.7, usage of this helper has mostly been replaced
 * 		by "direct packet access", enabling packet data to be
 * 		manipulated with *skb*\ **->data** and *skb*\ **->data_end**
 * 		poपूर्णांकing respectively to the first byte of packet data and to
 * 		the byte after the last byte of packet data. However, it
 * 		reमुख्यs useful अगर one wishes to पढ़ो large quantities of data
 * 		at once from a packet पूर्णांकo the eBPF stack.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_get_stackid(व्योम *ctx, काष्ठा bpf_map *map, u64 flags)
 * 	Description
 * 		Walk a user or a kernel stack and वापस its id. To achieve
 * 		this, the helper needs *ctx*, which is a poपूर्णांकer to the context
 * 		on which the tracing program is executed, and a poपूर्णांकer to a
 * 		*map* of type **BPF_MAP_TYPE_STACK_TRACE**.
 *
 * 		The last argument, *flags*, holds the number of stack frames to
 * 		skip (from 0 to 255), masked with
 * 		**BPF_F_SKIP_FIELD_MASK**. The next bits can be used to set
 * 		a combination of the following flags:
 *
 * 		**BPF_F_USER_STACK**
 * 			Collect a user space stack instead of a kernel stack.
 * 		**BPF_F_FAST_STACK_CMP**
 * 			Compare stacks by hash only.
 * 		**BPF_F_REUSE_STACKID**
 * 			If two dअगरferent stacks hash पूर्णांकo the same *stackid*,
 * 			discard the old one.
 *
 * 		The stack id retrieved is a 32 bit दीर्घ पूर्णांकeger handle which
 * 		can be further combined with other data (including other stack
 * 		ids) and used as a key पूर्णांकo maps. This can be useful क्रम
 * 		generating a variety of graphs (such as flame graphs or off-cpu
 * 		graphs).
 *
 * 		For walking a stack, this helper is an improvement over
 * 		**bpf_probe_पढ़ो**\ (), which can be used with unrolled loops
 * 		but is not efficient and consumes a lot of eBPF inकाष्ठाions.
 * 		Instead, **bpf_get_stackid**\ () can collect up to
 * 		**PERF_MAX_STACK_DEPTH** both kernel and user frames. Note that
 * 		this limit can be controlled with the **sysctl** program, and
 * 		that it should be manually increased in order to profile दीर्घ
 * 		user stacks (such as stacks क्रम Java programs). To करो so, use:
 *
 * 		::
 *
 * 			# sysctl kernel.perf_event_max_stack=<new value>
 * 	Return
 * 		The positive or null stack id on success, or a negative error
 * 		in हाल of failure.
 *
 * s64 bpf_csum_dअगरf(__be32 *from, u32 from_size, __be32 *to, u32 to_size, __wsum seed)
 * 	Description
 * 		Compute a checksum dअगरference, from the raw buffer poपूर्णांकed by
 * 		*from*, of length *from_size* (that must be a multiple of 4),
 * 		towards the raw buffer poपूर्णांकed by *to*, of size *to_size*
 * 		(same remark). An optional *seed* can be added to the value
 * 		(this can be cascaded, the seed may come from a previous call
 * 		to the helper).
 *
 * 		This is flexible enough to be used in several ways:
 *
 * 		* With *from_size* == 0, *to_size* > 0 and *seed* set to
 * 		  checksum, it can be used when pushing new data.
 * 		* With *from_size* > 0, *to_size* == 0 and *seed* set to
 * 		  checksum, it can be used when removing data from a packet.
 * 		* With *from_size* > 0, *to_size* > 0 and *seed* set to 0, it
 * 		  can be used to compute a dअगरf. Note that *from_size* and
 * 		  *to_size* करो not need to be equal.
 *
 * 		This helper can be used in combination with
 * 		**bpf_l3_csum_replace**\ () and **bpf_l4_csum_replace**\ (), to
 * 		which one can feed in the dअगरference computed with
 * 		**bpf_csum_dअगरf**\ ().
 * 	Return
 * 		The checksum result, or a negative error code in हाल of
 * 		failure.
 *
 * दीर्घ bpf_skb_get_tunnel_opt(काष्ठा sk_buff *skb, व्योम *opt, u32 size)
 * 	Description
 * 		Retrieve tunnel options metadata क्रम the packet associated to
 * 		*skb*, and store the raw tunnel option data to the buffer *opt*
 * 		of *size*.
 *
 * 		This helper can be used with encapsulation devices that can
 * 		operate in "collect metadata" mode (please refer to the related
 * 		note in the description of **bpf_skb_get_tunnel_key**\ () क्रम
 * 		more details). A particular example where this can be used is
 * 		in combination with the Geneve encapsulation protocol, where it
 * 		allows क्रम pushing (with **bpf_skb_get_tunnel_opt**\ () helper)
 * 		and retrieving arbitrary TLVs (Type-Length-Value headers) from
 * 		the eBPF program. This allows क्रम full customization of these
 * 		headers.
 * 	Return
 * 		The size of the option data retrieved.
 *
 * दीर्घ bpf_skb_set_tunnel_opt(काष्ठा sk_buff *skb, व्योम *opt, u32 size)
 * 	Description
 * 		Set tunnel options metadata क्रम the packet associated to *skb*
 * 		to the option data contained in the raw buffer *opt* of *size*.
 *
 * 		See also the description of the **bpf_skb_get_tunnel_opt**\ ()
 * 		helper क्रम additional inक्रमmation.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_skb_change_proto(काष्ठा sk_buff *skb, __be16 proto, u64 flags)
 * 	Description
 * 		Change the protocol of the *skb* to *proto*. Currently
 * 		supported are transition from IPv4 to IPv6, and from IPv6 to
 * 		IPv4. The helper takes care of the groundwork क्रम the
 * 		transition, including resizing the socket buffer. The eBPF
 * 		program is expected to fill the new headers, अगर any, via
 * 		**skb_store_bytes**\ () and to recompute the checksums with
 * 		**bpf_l3_csum_replace**\ () and **bpf_l4_csum_replace**\
 * 		(). The मुख्य हाल क्रम this helper is to perक्रमm NAT64
 * 		operations out of an eBPF program.
 *
 * 		Internally, the GSO type is marked as करोdgy so that headers are
 * 		checked and segments are recalculated by the GSO/GRO engine.
 * 		The size क्रम GSO target is adapted as well.
 *
 * 		All values क्रम *flags* are reserved क्रम future usage, and must
 * 		be left at zero.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_skb_change_type(काष्ठा sk_buff *skb, u32 type)
 * 	Description
 * 		Change the packet type क्रम the packet associated to *skb*. This
 * 		comes करोwn to setting *skb*\ **->pkt_type** to *type*, except
 * 		the eBPF program करोes not have a ग_लिखो access to *skb*\
 * 		**->pkt_type** beside this helper. Using a helper here allows
 * 		क्रम graceful handling of errors.
 *
 * 		The major use हाल is to change incoming *skb*s to
 * 		**PACKET_HOST** in a programmatic way instead of having to
 * 		recirculate via **redirect**\ (..., **BPF_F_INGRESS**), क्रम
 * 		example.
 *
 * 		Note that *type* only allows certain values. At this समय, they
 * 		are:
 *
 * 		**PACKET_HOST**
 * 			Packet is क्रम us.
 * 		**PACKET_BROADCAST**
 * 			Send packet to all.
 * 		**PACKET_MULTICAST**
 * 			Send packet to group.
 * 		**PACKET_OTHERHOST**
 * 			Send packet to someone अन्यथा.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_skb_under_cgroup(काष्ठा sk_buff *skb, काष्ठा bpf_map *map, u32 index)
 * 	Description
 * 		Check whether *skb* is a descendant of the cgroup2 held by
 * 		*map* of type **BPF_MAP_TYPE_CGROUP_ARRAY**, at *index*.
 * 	Return
 * 		The वापस value depends on the result of the test, and can be:
 *
 * 		* 0, अगर the *skb* failed the cgroup2 descendant test.
 * 		* 1, अगर the *skb* succeeded the cgroup2 descendant test.
 * 		* A negative error code, अगर an error occurred.
 *
 * u32 bpf_get_hash_recalc(काष्ठा sk_buff *skb)
 * 	Description
 * 		Retrieve the hash of the packet, *skb*\ **->hash**. If it is
 * 		not set, in particular अगर the hash was cleared due to mangling,
 * 		recompute this hash. Later accesses to the hash can be करोne
 * 		directly with *skb*\ **->hash**.
 *
 * 		Calling **bpf_set_hash_invalid**\ (), changing a packet
 * 		prototype with **bpf_skb_change_proto**\ (), or calling
 * 		**bpf_skb_store_bytes**\ () with the
 * 		**BPF_F_INVALIDATE_HASH** are actions susceptible to clear
 * 		the hash and to trigger a new computation क्रम the next call to
 * 		**bpf_get_hash_recalc**\ ().
 * 	Return
 * 		The 32-bit hash.
 *
 * u64 bpf_get_current_task(व्योम)
 * 	Return
 * 		A poपूर्णांकer to the current task काष्ठा.
 *
 * दीर्घ bpf_probe_ग_लिखो_user(व्योम *dst, स्थिर व्योम *src, u32 len)
 * 	Description
 * 		Attempt in a safe way to ग_लिखो *len* bytes from the buffer
 * 		*src* to *dst* in memory. It only works क्रम thपढ़ोs that are in
 * 		user context, and *dst* must be a valid user space address.
 *
 * 		This helper should not be used to implement any kind of
 * 		security mechanism because of TOC-TOU attacks, but rather to
 * 		debug, भागert, and manipulate execution of semi-cooperative
 * 		processes.
 *
 * 		Keep in mind that this feature is meant क्रम experiments, and it
 * 		has a risk of crashing the प्रणाली and running programs.
 * 		Thereक्रमe, when an eBPF program using this helper is attached,
 * 		a warning including PID and process name is prपूर्णांकed to kernel
 * 		logs.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_current_task_under_cgroup(काष्ठा bpf_map *map, u32 index)
 * 	Description
 * 		Check whether the probe is being run is the context of a given
 * 		subset of the cgroup2 hierarchy. The cgroup2 to test is held by
 * 		*map* of type **BPF_MAP_TYPE_CGROUP_ARRAY**, at *index*.
 * 	Return
 * 		The वापस value depends on the result of the test, and can be:
 *
 *		* 0, अगर current task beदीर्घs to the cgroup2.
 *		* 1, अगर current task करोes not beदीर्घ to the cgroup2.
 * 		* A negative error code, अगर an error occurred.
 *
 * दीर्घ bpf_skb_change_tail(काष्ठा sk_buff *skb, u32 len, u64 flags)
 * 	Description
 * 		Resize (trim or grow) the packet associated to *skb* to the
 * 		new *len*. The *flags* are reserved क्रम future usage, and must
 * 		be left at zero.
 *
 * 		The basic idea is that the helper perक्रमms the needed work to
 * 		change the size of the packet, then the eBPF program reग_लिखोs
 * 		the rest via helpers like **bpf_skb_store_bytes**\ (),
 * 		**bpf_l3_csum_replace**\ (), **bpf_l3_csum_replace**\ ()
 * 		and others. This helper is a slow path utility पूर्णांकended क्रम
 * 		replies with control messages. And because it is targeted क्रम
 * 		slow path, the helper itself can afक्रमd to be slow: it
 * 		implicitly linearizes, unclones and drops offloads from the
 * 		*skb*.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_skb_pull_data(काष्ठा sk_buff *skb, u32 len)
 * 	Description
 * 		Pull in non-linear data in हाल the *skb* is non-linear and not
 * 		all of *len* are part of the linear section. Make *len* bytes
 * 		from *skb* पढ़ोable and writable. If a zero value is passed क्रम
 * 		*len*, then the whole length of the *skb* is pulled.
 *
 * 		This helper is only needed क्रम पढ़ोing and writing with direct
 * 		packet access.
 *
 * 		For direct packet access, testing that offsets to access
 * 		are within packet boundaries (test on *skb*\ **->data_end**) is
 * 		susceptible to fail अगर offsets are invalid, or अगर the requested
 * 		data is in non-linear parts of the *skb*. On failure the
 * 		program can just bail out, or in the हाल of a non-linear
 * 		buffer, use a helper to make the data available. The
 * 		**bpf_skb_load_bytes**\ () helper is a first solution to access
 * 		the data. Another one consists in using **bpf_skb_pull_data**
 * 		to pull in once the non-linear parts, then retesting and
 * 		eventually access the data.
 *
 * 		At the same समय, this also makes sure the *skb* is uncloned,
 * 		which is a necessary condition क्रम direct ग_लिखो. As this needs
 * 		to be an invariant क्रम the ग_लिखो part only, the verअगरier
 * 		detects ग_लिखोs and adds a prologue that is calling
 * 		**bpf_skb_pull_data()** to effectively unclone the *skb* from
 * 		the very beginning in हाल it is indeed cloned.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * s64 bpf_csum_update(काष्ठा sk_buff *skb, __wsum csum)
 * 	Description
 * 		Add the checksum *csum* पूर्णांकo *skb*\ **->csum** in हाल the
 * 		driver has supplied a checksum क्रम the entire packet पूर्णांकo that
 * 		field. Return an error otherwise. This helper is पूर्णांकended to be
 * 		used in combination with **bpf_csum_dअगरf**\ (), in particular
 * 		when the checksum needs to be updated after data has been
 * 		written पूर्णांकo the packet through direct packet access.
 * 	Return
 * 		The checksum on success, or a negative error code in हाल of
 * 		failure.
 *
 * व्योम bpf_set_hash_invalid(काष्ठा sk_buff *skb)
 * 	Description
 * 		Invalidate the current *skb*\ **->hash**. It can be used after
 * 		mangling on headers through direct packet access, in order to
 * 		indicate that the hash is outdated and to trigger a
 * 		recalculation the next समय the kernel tries to access this
 * 		hash or when the **bpf_get_hash_recalc**\ () helper is called.
 *
 * दीर्घ bpf_get_numa_node_id(व्योम)
 * 	Description
 * 		Return the id of the current NUMA node. The primary use हाल
 * 		क्रम this helper is the selection of sockets क्रम the local NUMA
 * 		node, when the program is attached to sockets using the
 * 		**SO_ATTACH_REUSEPORT_EBPF** option (see also **socket(7)**),
 * 		but the helper is also available to other eBPF program types,
 * 		similarly to **bpf_get_smp_processor_id**\ ().
 * 	Return
 * 		The id of current NUMA node.
 *
 * दीर्घ bpf_skb_change_head(काष्ठा sk_buff *skb, u32 len, u64 flags)
 * 	Description
 * 		Grows headroom of packet associated to *skb* and adjusts the
 * 		offset of the MAC header accordingly, adding *len* bytes of
 * 		space. It स्वतःmatically extends and पुनः_स्मृतिates memory as
 * 		required.
 *
 * 		This helper can be used on a layer 3 *skb* to push a MAC header
 * 		क्रम redirection पूर्णांकo a layer 2 device.
 *
 * 		All values क्रम *flags* are reserved क्रम future usage, and must
 * 		be left at zero.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_xdp_adjust_head(काष्ठा xdp_buff *xdp_md, पूर्णांक delta)
 * 	Description
 * 		Adjust (move) *xdp_md*\ **->data** by *delta* bytes. Note that
 * 		it is possible to use a negative value क्रम *delta*. This helper
 * 		can be used to prepare the packet क्रम pushing or popping
 * 		headers.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_probe_पढ़ो_str(व्योम *dst, u32 size, स्थिर व्योम *unsafe_ptr)
 * 	Description
 * 		Copy a NUL terminated string from an unsafe kernel address
 * 		*unsafe_ptr* to *dst*. See **bpf_probe_पढ़ो_kernel_str**\ () क्रम
 * 		more details.
 *
 * 		Generally, use **bpf_probe_पढ़ो_user_str**\ () or
 * 		**bpf_probe_पढ़ो_kernel_str**\ () instead.
 * 	Return
 * 		On success, the strictly positive length of the string,
 * 		including the trailing NUL अक्षरacter. On error, a negative
 * 		value.
 *
 * u64 bpf_get_socket_cookie(काष्ठा sk_buff *skb)
 * 	Description
 * 		If the **काष्ठा sk_buff** poपूर्णांकed by *skb* has a known socket,
 * 		retrieve the cookie (generated by the kernel) of this socket.
 * 		If no cookie has been set yet, generate a new cookie. Once
 * 		generated, the socket cookie reमुख्यs stable क्रम the lअगरe of the
 * 		socket. This helper can be useful क्रम monitoring per socket
 * 		networking traffic statistics as it provides a global socket
 * 		identअगरier that can be assumed unique.
 * 	Return
 * 		A 8-byte दीर्घ unique number on success, or 0 अगर the socket
 * 		field is missing inside *skb*.
 *
 * u64 bpf_get_socket_cookie(काष्ठा bpf_sock_addr *ctx)
 * 	Description
 * 		Equivalent to bpf_get_socket_cookie() helper that accepts
 * 		*skb*, but माला_लो socket from **काष्ठा bpf_sock_addr** context.
 * 	Return
 * 		A 8-byte दीर्घ unique number.
 *
 * u64 bpf_get_socket_cookie(काष्ठा bpf_sock_ops *ctx)
 * 	Description
 * 		Equivalent to **bpf_get_socket_cookie**\ () helper that accepts
 * 		*skb*, but माला_लो socket from **काष्ठा bpf_sock_ops** context.
 * 	Return
 * 		A 8-byte दीर्घ unique number.
 *
 * u64 bpf_get_socket_cookie(काष्ठा sock *sk)
 * 	Description
 * 		Equivalent to **bpf_get_socket_cookie**\ () helper that accepts
 * 		*sk*, but माला_लो socket from a BTF **काष्ठा sock**. This helper
 * 		also works क्रम sleepable programs.
 * 	Return
 * 		A 8-byte दीर्घ unique number or 0 अगर *sk* is शून्य.
 *
 * u32 bpf_get_socket_uid(काष्ठा sk_buff *skb)
 * 	Return
 * 		The owner UID of the socket associated to *skb*. If the socket
 * 		is **शून्य**, or अगर it is not a full socket (i.e. अगर it is a
 * 		समय-रुको or a request socket instead), **overflowuid** value
 * 		is वापसed (note that **overflowuid** might also be the actual
 * 		UID value क्रम the socket).
 *
 * दीर्घ bpf_set_hash(काष्ठा sk_buff *skb, u32 hash)
 * 	Description
 * 		Set the full hash क्रम *skb* (set the field *skb*\ **->hash**)
 * 		to value *hash*.
 * 	Return
 * 		0
 *
 * दीर्घ bpf_setsockopt(व्योम *bpf_socket, पूर्णांक level, पूर्णांक optname, व्योम *optval, पूर्णांक optlen)
 * 	Description
 * 		Emulate a call to **setsockopt()** on the socket associated to
 * 		*bpf_socket*, which must be a full socket. The *level* at
 * 		which the option resides and the name *optname* of the option
 * 		must be specअगरied, see **setsockopt(2)** क्रम more inक्रमmation.
 * 		The option value of length *optlen* is poपूर्णांकed by *optval*.
 *
 * 		*bpf_socket* should be one of the following:
 *
 * 		* **काष्ठा bpf_sock_ops** क्रम **BPF_PROG_TYPE_SOCK_OPS**.
 * 		* **काष्ठा bpf_sock_addr** क्रम **BPF_CGROUP_INET4_CONNECT**
 * 		  and **BPF_CGROUP_INET6_CONNECT**.
 *
 * 		This helper actually implements a subset of **setsockopt()**.
 * 		It supports the following *level*\ s:
 *
 * 		* **SOL_SOCKET**, which supports the following *optname*\ s:
 * 		  **SO_RCVBUF**, **SO_SNDBUF**, **SO_MAX_PACING_RATE**,
 * 		  **SO_PRIORITY**, **SO_RCVLOWAT**, **SO_MARK**,
 * 		  **SO_BINDTODEVICE**, **SO_KEEPALIVE**.
 * 		* **IPPROTO_TCP**, which supports the following *optname*\ s:
 * 		  **TCP_CONGESTION**, **TCP_BPF_IW**,
 * 		  **TCP_BPF_SNDCWND_CLAMP**, **TCP_SAVE_SYN**,
 * 		  **TCP_KEEPIDLE**, **TCP_KEEPINTVL**, **TCP_KEEPCNT**,
 *		  **TCP_SYNCNT**, **TCP_USER_TIMEOUT**, **TCP_NOTSENT_LOWAT**.
 * 		* **IPPROTO_IP**, which supports *optname* **IP_TOS**.
 * 		* **IPPROTO_IPV6**, which supports *optname* **IPV6_TCLASS**.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_skb_adjust_room(काष्ठा sk_buff *skb, s32 len_dअगरf, u32 mode, u64 flags)
 * 	Description
 * 		Grow or shrink the room क्रम data in the packet associated to
 * 		*skb* by *len_dअगरf*, and according to the selected *mode*.
 *
 * 		By शेष, the helper will reset any offloaded checksum
 * 		indicator of the skb to CHECKSUM_NONE. This can be aव्योमed
 * 		by the following flag:
 *
 * 		* **BPF_F_ADJ_ROOM_NO_CSUM_RESET**: Do not reset offloaded
 * 		  checksum data of the skb to CHECKSUM_NONE.
 *
 *		There are two supported modes at this समय:
 *
 *		* **BPF_ADJ_ROOM_MAC**: Adjust room at the mac layer
 *		  (room space is added or हटाओd below the layer 2 header).
 *
 * 		* **BPF_ADJ_ROOM_NET**: Adjust room at the network layer
 * 		  (room space is added or हटाओd below the layer 3 header).
 *
 *		The following flags are supported at this समय:
 *
 *		* **BPF_F_ADJ_ROOM_FIXED_GSO**: Do not adjust gso_size.
 *		  Adjusting mss in this way is not allowed क्रम datagrams.
 *
 *		* **BPF_F_ADJ_ROOM_ENCAP_L3_IPV4**,
 *		  **BPF_F_ADJ_ROOM_ENCAP_L3_IPV6**:
 *		  Any new space is reserved to hold a tunnel header.
 *		  Configure skb offsets and other fields accordingly.
 *
 *		* **BPF_F_ADJ_ROOM_ENCAP_L4_GRE**,
 *		  **BPF_F_ADJ_ROOM_ENCAP_L4_UDP**:
 *		  Use with ENCAP_L3 flags to further specअगरy the tunnel type.
 *
 *		* **BPF_F_ADJ_ROOM_ENCAP_L2**\ (*len*):
 *		  Use with ENCAP_L3/L4 flags to further specअगरy the tunnel
 *		  type; *len* is the length of the inner MAC header.
 *
 *		* **BPF_F_ADJ_ROOM_ENCAP_L2_ETH**:
 *		  Use with BPF_F_ADJ_ROOM_ENCAP_L2 flag to further specअगरy the
 *		  L2 type as Ethernet.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_redirect_map(काष्ठा bpf_map *map, u32 key, u64 flags)
 * 	Description
 * 		Redirect the packet to the endpoपूर्णांक referenced by *map* at
 * 		index *key*. Depending on its type, this *map* can contain
 * 		references to net devices (क्रम क्रमwarding packets through other
 * 		ports), or to CPUs (क्रम redirecting XDP frames to another CPU;
 * 		but this is only implemented क्रम native XDP (with driver
 * 		support) as of this writing).
 *
 * 		The lower two bits of *flags* are used as the वापस code अगर
 * 		the map lookup fails. This is so that the वापस value can be
 * 		one of the XDP program वापस codes up to **XDP_TX**, as chosen
 * 		by the caller. Any higher bits in the *flags* argument must be
 * 		unset.
 *
 * 		See also **bpf_redirect**\ (), which only supports redirecting
 * 		to an अगरindex, but करोesn't require a map to करो so.
 * 	Return
 * 		**XDP_REसूचीECT** on success, or the value of the two lower bits
 * 		of the *flags* argument on error.
 *
 * दीर्घ bpf_sk_redirect_map(काष्ठा sk_buff *skb, काष्ठा bpf_map *map, u32 key, u64 flags)
 * 	Description
 * 		Redirect the packet to the socket referenced by *map* (of type
 * 		**BPF_MAP_TYPE_SOCKMAP**) at index *key*. Both ingress and
 * 		egress पूर्णांकerfaces can be used क्रम redirection. The
 * 		**BPF_F_INGRESS** value in *flags* is used to make the
 * 		distinction (ingress path is selected अगर the flag is present,
 * 		egress path otherwise). This is the only flag supported क्रम now.
 * 	Return
 * 		**SK_PASS** on success, or **SK_DROP** on error.
 *
 * दीर्घ bpf_sock_map_update(काष्ठा bpf_sock_ops *skops, काष्ठा bpf_map *map, व्योम *key, u64 flags)
 * 	Description
 * 		Add an entry to, or update a *map* referencing sockets. The
 * 		*skops* is used as a new value क्रम the entry associated to
 * 		*key*. *flags* is one of:
 *
 * 		**BPF_NOEXIST**
 * 			The entry क्रम *key* must not exist in the map.
 * 		**BPF_EXIST**
 * 			The entry क्रम *key* must alपढ़ोy exist in the map.
 * 		**BPF_ANY**
 * 			No condition on the existence of the entry क्रम *key*.
 *
 * 		If the *map* has eBPF programs (parser and verdict), those will
 * 		be inherited by the socket being added. If the socket is
 * 		alपढ़ोy attached to eBPF programs, this results in an error.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_xdp_adjust_meta(काष्ठा xdp_buff *xdp_md, पूर्णांक delta)
 * 	Description
 * 		Adjust the address poपूर्णांकed by *xdp_md*\ **->data_meta** by
 * 		*delta* (which can be positive or negative). Note that this
 * 		operation modअगरies the address stored in *xdp_md*\ **->data**,
 * 		so the latter must be loaded only after the helper has been
 * 		called.
 *
 * 		The use of *xdp_md*\ **->data_meta** is optional and programs
 * 		are not required to use it. The rationale is that when the
 * 		packet is processed with XDP (e.g. as DoS filter), it is
 * 		possible to push further meta data aदीर्घ with it beक्रमe passing
 * 		to the stack, and to give the guarantee that an ingress eBPF
 * 		program attached as a TC classअगरier on the same device can pick
 * 		this up क्रम further post-processing. Since TC works with socket
 * 		buffers, it reमुख्यs possible to set from XDP the **mark** or
 * 		**priority** poपूर्णांकers, or other poपूर्णांकers क्रम the socket buffer.
 * 		Having this scratch space generic and programmable allows क्रम
 * 		more flexibility as the user is मुक्त to store whatever meta
 * 		data they need.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_perf_event_पढ़ो_value(काष्ठा bpf_map *map, u64 flags, काष्ठा bpf_perf_event_value *buf, u32 buf_size)
 * 	Description
 * 		Read the value of a perf event counter, and store it पूर्णांकo *buf*
 * 		of size *buf_size*. This helper relies on a *map* of type
 * 		**BPF_MAP_TYPE_PERF_EVENT_ARRAY**. The nature of the perf event
 * 		counter is selected when *map* is updated with perf event file
 * 		descriptors. The *map* is an array whose size is the number of
 * 		available CPUs, and each cell contains a value relative to one
 * 		CPU. The value to retrieve is indicated by *flags*, that
 * 		contains the index of the CPU to look up, masked with
 * 		**BPF_F_INDEX_MASK**. Alternatively, *flags* can be set to
 * 		**BPF_F_CURRENT_CPU** to indicate that the value क्रम the
 * 		current CPU should be retrieved.
 *
 * 		This helper behaves in a way बंद to
 * 		**bpf_perf_event_पढ़ो**\ () helper, save that instead of
 * 		just वापसing the value observed, it fills the *buf*
 * 		काष्ठाure. This allows क्रम additional data to be retrieved: in
 * 		particular, the enabled and running बार (in *buf*\
 * 		**->enabled** and *buf*\ **->running**, respectively) are
 * 		copied. In general, **bpf_perf_event_पढ़ो_value**\ () is
 * 		recommended over **bpf_perf_event_पढ़ो**\ (), which has some
 * 		ABI issues and provides fewer functionalities.
 *
 * 		These values are पूर्णांकeresting, because hardware PMU (Perक्रमmance
 * 		Monitoring Unit) counters are limited resources. When there are
 * 		more PMU based perf events खोलोed than available counters,
 * 		kernel will multiplex these events so each event माला_लो certain
 * 		percentage (but not all) of the PMU समय. In हाल that
 * 		multiplexing happens, the number of samples or counter value
 * 		will not reflect the हाल compared to when no multiplexing
 * 		occurs. This makes comparison between dअगरferent runs dअगरficult.
 * 		Typically, the counter value should be normalized beक्रमe
 * 		comparing to other experiments. The usual normalization is करोne
 * 		as follows.
 *
 * 		::
 *
 * 			normalized_counter = counter * t_enabled / t_running
 *
 * 		Where t_enabled is the समय enabled क्रम event and t_running is
 * 		the समय running क्रम event since last normalization. The
 * 		enabled and running बार are accumulated since the perf event
 * 		खोलो. To achieve scaling factor between two invocations of an
 * 		eBPF program, users can use CPU id as the key (which is
 * 		typical क्रम perf array usage model) to remember the previous
 * 		value and करो the calculation inside the eBPF program.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_perf_prog_पढ़ो_value(काष्ठा bpf_perf_event_data *ctx, काष्ठा bpf_perf_event_value *buf, u32 buf_size)
 * 	Description
 * 		For en eBPF program attached to a perf event, retrieve the
 * 		value of the event counter associated to *ctx* and store it in
 * 		the काष्ठाure poपूर्णांकed by *buf* and of size *buf_size*. Enabled
 * 		and running बार are also stored in the काष्ठाure (see
 * 		description of helper **bpf_perf_event_पढ़ो_value**\ () क्रम
 * 		more details).
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_माला_लोockopt(व्योम *bpf_socket, पूर्णांक level, पूर्णांक optname, व्योम *optval, पूर्णांक optlen)
 * 	Description
 * 		Emulate a call to **माला_लोockopt()** on the socket associated to
 * 		*bpf_socket*, which must be a full socket. The *level* at
 * 		which the option resides and the name *optname* of the option
 * 		must be specअगरied, see **माला_लोockopt(2)** क्रम more inक्रमmation.
 * 		The retrieved value is stored in the काष्ठाure poपूर्णांकed by
 * 		*opval* and of length *optlen*.
 *
 * 		*bpf_socket* should be one of the following:
 *
 * 		* **काष्ठा bpf_sock_ops** क्रम **BPF_PROG_TYPE_SOCK_OPS**.
 * 		* **काष्ठा bpf_sock_addr** क्रम **BPF_CGROUP_INET4_CONNECT**
 * 		  and **BPF_CGROUP_INET6_CONNECT**.
 *
 * 		This helper actually implements a subset of **माला_लोockopt()**.
 * 		It supports the following *level*\ s:
 *
 * 		* **IPPROTO_TCP**, which supports *optname*
 * 		  **TCP_CONGESTION**.
 * 		* **IPPROTO_IP**, which supports *optname* **IP_TOS**.
 * 		* **IPPROTO_IPV6**, which supports *optname* **IPV6_TCLASS**.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_override_वापस(काष्ठा pt_regs *regs, u64 rc)
 * 	Description
 * 		Used क्रम error injection, this helper uses kprobes to override
 * 		the वापस value of the probed function, and to set it to *rc*.
 * 		The first argument is the context *regs* on which the kprobe
 * 		works.
 *
 * 		This helper works by setting the PC (program counter)
 * 		to an override function which is run in place of the original
 * 		probed function. This means the probed function is not run at
 * 		all. The replacement function just वापसs with the required
 * 		value.
 *
 * 		This helper has security implications, and thus is subject to
 * 		restrictions. It is only available अगर the kernel was compiled
 * 		with the **CONFIG_BPF_KPROBE_OVERRIDE** configuration
 * 		option, and in this हाल it only works on functions tagged with
 * 		**ALLOW_ERROR_INJECTION** in the kernel code.
 *
 * 		Also, the helper is only available क्रम the architectures having
 * 		the CONFIG_FUNCTION_ERROR_INJECTION option. As of this writing,
 * 		x86 architecture is the only one to support this feature.
 * 	Return
 * 		0
 *
 * दीर्घ bpf_sock_ops_cb_flags_set(काष्ठा bpf_sock_ops *bpf_sock, पूर्णांक argval)
 * 	Description
 * 		Attempt to set the value of the **bpf_sock_ops_cb_flags** field
 * 		क्रम the full TCP socket associated to *bpf_sock_ops* to
 * 		*argval*.
 *
 * 		The primary use of this field is to determine अगर there should
 * 		be calls to eBPF programs of type
 * 		**BPF_PROG_TYPE_SOCK_OPS** at various poपूर्णांकs in the TCP
 * 		code. A program of the same type can change its value, per
 * 		connection and as necessary, when the connection is
 * 		established. This field is directly accessible क्रम पढ़ोing, but
 * 		this helper must be used क्रम updates in order to वापस an
 * 		error अगर an eBPF program tries to set a callback that is not
 * 		supported in the current kernel.
 *
 * 		*argval* is a flag array which can combine these flags:
 *
 * 		* **BPF_SOCK_OPS_RTO_CB_FLAG** (retransmission समय out)
 * 		* **BPF_SOCK_OPS_RETRANS_CB_FLAG** (retransmission)
 * 		* **BPF_SOCK_OPS_STATE_CB_FLAG** (TCP state change)
 * 		* **BPF_SOCK_OPS_RTT_CB_FLAG** (every RTT)
 *
 * 		Thereक्रमe, this function can be used to clear a callback flag by
 * 		setting the appropriate bit to zero. e.g. to disable the RTO
 * 		callback:
 *
 * 		**bpf_sock_ops_cb_flags_set(bpf_sock,**
 * 			**bpf_sock->bpf_sock_ops_cb_flags & ~BPF_SOCK_OPS_RTO_CB_FLAG)**
 *
 * 		Here are some examples of where one could call such eBPF
 * 		program:
 *
 * 		* When RTO fires.
 * 		* When a packet is retransmitted.
 * 		* When the connection terminates.
 * 		* When a packet is sent.
 * 		* When a packet is received.
 * 	Return
 * 		Code **-EINVAL** अगर the socket is not a full TCP socket;
 * 		otherwise, a positive number containing the bits that could not
 * 		be set is वापसed (which comes करोwn to 0 अगर all bits were set
 * 		as required).
 *
 * दीर्घ bpf_msg_redirect_map(काष्ठा sk_msg_buff *msg, काष्ठा bpf_map *map, u32 key, u64 flags)
 * 	Description
 * 		This helper is used in programs implementing policies at the
 * 		socket level. If the message *msg* is allowed to pass (i.e. अगर
 * 		the verdict eBPF program वापसs **SK_PASS**), redirect it to
 * 		the socket referenced by *map* (of type
 * 		**BPF_MAP_TYPE_SOCKMAP**) at index *key*. Both ingress and
 * 		egress पूर्णांकerfaces can be used क्रम redirection. The
 * 		**BPF_F_INGRESS** value in *flags* is used to make the
 * 		distinction (ingress path is selected अगर the flag is present,
 * 		egress path otherwise). This is the only flag supported क्रम now.
 * 	Return
 * 		**SK_PASS** on success, or **SK_DROP** on error.
 *
 * दीर्घ bpf_msg_apply_bytes(काष्ठा sk_msg_buff *msg, u32 bytes)
 * 	Description
 * 		For socket policies, apply the verdict of the eBPF program to
 * 		the next *bytes* (number of bytes) of message *msg*.
 *
 * 		For example, this helper can be used in the following हालs:
 *
 * 		* A single **sendmsg**\ () or **sendfile**\ () प्रणाली call
 * 		  contains multiple logical messages that the eBPF program is
 * 		  supposed to पढ़ो and क्रम which it should apply a verdict.
 * 		* An eBPF program only cares to पढ़ो the first *bytes* of a
 * 		  *msg*. If the message has a large payload, then setting up
 * 		  and calling the eBPF program repeatedly क्रम all bytes, even
 * 		  though the verdict is alपढ़ोy known, would create unnecessary
 * 		  overhead.
 *
 * 		When called from within an eBPF program, the helper sets a
 * 		counter पूर्णांकernal to the BPF infraकाष्ठाure, that is used to
 * 		apply the last verdict to the next *bytes*. If *bytes* is
 * 		smaller than the current data being processed from a
 * 		**sendmsg**\ () or **sendfile**\ () प्रणाली call, the first
 * 		*bytes* will be sent and the eBPF program will be re-run with
 * 		the poपूर्णांकer क्रम start of data poपूर्णांकing to byte number *bytes*
 * 		**+ 1**. If *bytes* is larger than the current data being
 * 		processed, then the eBPF verdict will be applied to multiple
 * 		**sendmsg**\ () or **sendfile**\ () calls until *bytes* are
 * 		consumed.
 *
 * 		Note that अगर a socket बंदs with the पूर्णांकernal counter holding
 * 		a non-zero value, this is not a problem because data is not
 * 		being buffered क्रम *bytes* and is sent as it is received.
 * 	Return
 * 		0
 *
 * दीर्घ bpf_msg_cork_bytes(काष्ठा sk_msg_buff *msg, u32 bytes)
 * 	Description
 * 		For socket policies, prevent the execution of the verdict eBPF
 * 		program क्रम message *msg* until *bytes* (byte number) have been
 * 		accumulated.
 *
 * 		This can be used when one needs a specअगरic number of bytes
 * 		beक्रमe a verdict can be asचिन्हित, even अगर the data spans
 * 		multiple **sendmsg**\ () or **sendfile**\ () calls. The extreme
 * 		हाल would be a user calling **sendmsg**\ () repeatedly with
 * 		1-byte दीर्घ message segments. Obviously, this is bad क्रम
 * 		perक्रमmance, but it is still valid. If the eBPF program needs
 * 		*bytes* bytes to validate a header, this helper can be used to
 * 		prevent the eBPF program to be called again until *bytes* have
 * 		been accumulated.
 * 	Return
 * 		0
 *
 * दीर्घ bpf_msg_pull_data(काष्ठा sk_msg_buff *msg, u32 start, u32 end, u64 flags)
 * 	Description
 * 		For socket policies, pull in non-linear data from user space
 * 		क्रम *msg* and set poपूर्णांकers *msg*\ **->data** and *msg*\
 * 		**->data_end** to *start* and *end* bytes offsets पूर्णांकo *msg*,
 * 		respectively.
 *
 * 		If a program of type **BPF_PROG_TYPE_SK_MSG** is run on a
 * 		*msg* it can only parse data that the (**data**, **data_end**)
 * 		poपूर्णांकers have alपढ़ोy consumed. For **sendmsg**\ () hooks this
 * 		is likely the first scatterlist element. But क्रम calls relying
 * 		on the **sendpage** handler (e.g. **sendfile**\ ()) this will
 * 		be the range (**0**, **0**) because the data is shared with
 * 		user space and by शेष the objective is to aव्योम allowing
 * 		user space to modअगरy data जबतक (or after) eBPF verdict is
 * 		being decided. This helper can be used to pull in data and to
 * 		set the start and end poपूर्णांकer to given values. Data will be
 * 		copied अगर necessary (i.e. अगर data was not linear and अगर start
 * 		and end poपूर्णांकers करो not poपूर्णांक to the same chunk).
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 *
 * 		All values क्रम *flags* are reserved क्रम future usage, and must
 * 		be left at zero.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_bind(काष्ठा bpf_sock_addr *ctx, काष्ठा sockaddr *addr, पूर्णांक addr_len)
 * 	Description
 * 		Bind the socket associated to *ctx* to the address poपूर्णांकed by
 * 		*addr*, of length *addr_len*. This allows क्रम making outgoing
 * 		connection from the desired IP address, which can be useful क्रम
 * 		example when all processes inside a cgroup should use one
 * 		single IP address on a host that has multiple IP configured.
 *
 * 		This helper works क्रम IPv4 and IPv6, TCP and UDP sockets. The
 * 		करोमुख्य (*addr*\ **->sa_family**) must be **AF_INET** (or
 * 		**AF_INET6**). It's advised to pass zero port (**sin_port**
 * 		or **sin6_port**) which triggers IP_BIND_ADDRESS_NO_PORT-like
 * 		behavior and lets the kernel efficiently pick up an unused
 * 		port as दीर्घ as 4-tuple is unique. Passing non-zero port might
 * 		lead to degraded perक्रमmance.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_xdp_adjust_tail(काष्ठा xdp_buff *xdp_md, पूर्णांक delta)
 * 	Description
 * 		Adjust (move) *xdp_md*\ **->data_end** by *delta* bytes. It is
 * 		possible to both shrink and grow the packet tail.
 * 		Shrink करोne via *delta* being a negative पूर्णांकeger.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_skb_get_xfrm_state(काष्ठा sk_buff *skb, u32 index, काष्ठा bpf_xfrm_state *xfrm_state, u32 size, u64 flags)
 * 	Description
 * 		Retrieve the XFRM state (IP transक्रमm framework, see also
 * 		**ip-xfrm(8)**) at *index* in XFRM "security path" क्रम *skb*.
 *
 * 		The retrieved value is stored in the **काष्ठा bpf_xfrm_state**
 * 		poपूर्णांकed by *xfrm_state* and of length *size*.
 *
 * 		All values क्रम *flags* are reserved क्रम future usage, and must
 * 		be left at zero.
 *
 * 		This helper is available only अगर the kernel was compiled with
 * 		**CONFIG_XFRM** configuration option.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_get_stack(व्योम *ctx, व्योम *buf, u32 size, u64 flags)
 * 	Description
 * 		Return a user or a kernel stack in bpf program provided buffer.
 * 		To achieve this, the helper needs *ctx*, which is a poपूर्णांकer
 * 		to the context on which the tracing program is executed.
 * 		To store the stacktrace, the bpf program provides *buf* with
 * 		a nonnegative *size*.
 *
 * 		The last argument, *flags*, holds the number of stack frames to
 * 		skip (from 0 to 255), masked with
 * 		**BPF_F_SKIP_FIELD_MASK**. The next bits can be used to set
 * 		the following flags:
 *
 * 		**BPF_F_USER_STACK**
 * 			Collect a user space stack instead of a kernel stack.
 * 		**BPF_F_USER_BUILD_ID**
 * 			Collect buildid+offset instead of ips क्रम user stack,
 * 			only valid अगर **BPF_F_USER_STACK** is also specअगरied.
 *
 * 		**bpf_get_stack**\ () can collect up to
 * 		**PERF_MAX_STACK_DEPTH** both kernel and user frames, subject
 * 		to sufficient large buffer size. Note that
 * 		this limit can be controlled with the **sysctl** program, and
 * 		that it should be manually increased in order to profile दीर्घ
 * 		user stacks (such as stacks क्रम Java programs). To करो so, use:
 *
 * 		::
 *
 * 			# sysctl kernel.perf_event_max_stack=<new value>
 * 	Return
 * 		A non-negative value equal to or less than *size* on success,
 * 		or a negative error in हाल of failure.
 *
 * दीर्घ bpf_skb_load_bytes_relative(स्थिर व्योम *skb, u32 offset, व्योम *to, u32 len, u32 start_header)
 * 	Description
 * 		This helper is similar to **bpf_skb_load_bytes**\ () in that
 * 		it provides an easy way to load *len* bytes from *offset*
 * 		from the packet associated to *skb*, पूर्णांकo the buffer poपूर्णांकed
 * 		by *to*. The dअगरference to **bpf_skb_load_bytes**\ () is that
 * 		a fअगरth argument *start_header* exists in order to select a
 * 		base offset to start from. *start_header* can be one of:
 *
 * 		**BPF_HDR_START_MAC**
 * 			Base offset to load data from is *skb*'s mac header.
 * 		**BPF_HDR_START_NET**
 * 			Base offset to load data from is *skb*'s network header.
 *
 * 		In general, "direct packet access" is the preferred method to
 * 		access packet data, however, this helper is in particular useful
 * 		in socket filters where *skb*\ **->data** करोes not always poपूर्णांक
 * 		to the start of the mac header and where "direct packet access"
 * 		is not available.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_fib_lookup(व्योम *ctx, काष्ठा bpf_fib_lookup *params, पूर्णांक plen, u32 flags)
 *	Description
 *		Do FIB lookup in kernel tables using parameters in *params*.
 *		If lookup is successful and result shows packet is to be
 *		क्रमwarded, the neighbor tables are searched क्रम the nexthop.
 *		If successful (ie., FIB lookup shows क्रमwarding and nexthop
 *		is resolved), the nexthop address is वापसed in ipv4_dst
 *		or ipv6_dst based on family, smac is set to mac address of
 *		egress device, dmac is set to nexthop mac address, rt_metric
 *		is set to metric from route (IPv4/IPv6 only), and अगरindex
 *		is set to the device index of the nexthop from the FIB lookup.
 *
 *		*plen* argument is the size of the passed in काष्ठा.
 *		*flags* argument can be a combination of one or more of the
 *		following values:
 *
 *		**BPF_FIB_LOOKUP_सूचीECT**
 *			Do a direct table lookup vs full lookup using FIB
 *			rules.
 *		**BPF_FIB_LOOKUP_OUTPUT**
 *			Perक्रमm lookup from an egress perspective (शेष is
 *			ingress).
 *
 *		*ctx* is either **काष्ठा xdp_md** क्रम XDP programs or
 *		**काष्ठा sk_buff** tc cls_act programs.
 *	Return
 *		* < 0 अगर any input argument is invalid
 *		*   0 on success (packet is क्रमwarded, nexthop neighbor exists)
 *		* > 0 one of **BPF_FIB_LKUP_RET_** codes explaining why the
 *		  packet is not क्रमwarded or needs assist from full stack
 *
 *		If lookup fails with BPF_FIB_LKUP_RET_FRAG_NEEDED, then the MTU
 *		was exceeded and output params->mtu_result contains the MTU.
 *
 * दीर्घ bpf_sock_hash_update(काष्ठा bpf_sock_ops *skops, काष्ठा bpf_map *map, व्योम *key, u64 flags)
 *	Description
 *		Add an entry to, or update a sockhash *map* referencing sockets.
 *		The *skops* is used as a new value क्रम the entry associated to
 *		*key*. *flags* is one of:
 *
 *		**BPF_NOEXIST**
 *			The entry क्रम *key* must not exist in the map.
 *		**BPF_EXIST**
 *			The entry क्रम *key* must alपढ़ोy exist in the map.
 *		**BPF_ANY**
 *			No condition on the existence of the entry क्रम *key*.
 *
 *		If the *map* has eBPF programs (parser and verdict), those will
 *		be inherited by the socket being added. If the socket is
 *		alपढ़ोy attached to eBPF programs, this results in an error.
 *	Return
 *		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_msg_redirect_hash(काष्ठा sk_msg_buff *msg, काष्ठा bpf_map *map, व्योम *key, u64 flags)
 *	Description
 *		This helper is used in programs implementing policies at the
 *		socket level. If the message *msg* is allowed to pass (i.e. अगर
 *		the verdict eBPF program वापसs **SK_PASS**), redirect it to
 *		the socket referenced by *map* (of type
 *		**BPF_MAP_TYPE_SOCKHASH**) using hash *key*. Both ingress and
 *		egress पूर्णांकerfaces can be used क्रम redirection. The
 *		**BPF_F_INGRESS** value in *flags* is used to make the
 *		distinction (ingress path is selected अगर the flag is present,
 *		egress path otherwise). This is the only flag supported क्रम now.
 *	Return
 *		**SK_PASS** on success, or **SK_DROP** on error.
 *
 * दीर्घ bpf_sk_redirect_hash(काष्ठा sk_buff *skb, काष्ठा bpf_map *map, व्योम *key, u64 flags)
 *	Description
 *		This helper is used in programs implementing policies at the
 *		skb socket level. If the sk_buff *skb* is allowed to pass (i.e.
 *		अगर the verdict eBPF program वापसs **SK_PASS**), redirect it
 *		to the socket referenced by *map* (of type
 *		**BPF_MAP_TYPE_SOCKHASH**) using hash *key*. Both ingress and
 *		egress पूर्णांकerfaces can be used क्रम redirection. The
 *		**BPF_F_INGRESS** value in *flags* is used to make the
 *		distinction (ingress path is selected अगर the flag is present,
 *		egress otherwise). This is the only flag supported क्रम now.
 *	Return
 *		**SK_PASS** on success, or **SK_DROP** on error.
 *
 * दीर्घ bpf_lwt_push_encap(काष्ठा sk_buff *skb, u32 type, व्योम *hdr, u32 len)
 *	Description
 *		Encapsulate the packet associated to *skb* within a Layer 3
 *		protocol header. This header is provided in the buffer at
 *		address *hdr*, with *len* its size in bytes. *type* indicates
 *		the protocol of the header and can be one of:
 *
 *		**BPF_LWT_ENCAP_SEG6**
 *			IPv6 encapsulation with Segment Routing Header
 *			(**काष्ठा ipv6_sr_hdr**). *hdr* only contains the SRH,
 *			the IPv6 header is computed by the kernel.
 *		**BPF_LWT_ENCAP_SEG6_INLINE**
 *			Only works अगर *skb* contains an IPv6 packet. Insert a
 *			Segment Routing Header (**काष्ठा ipv6_sr_hdr**) inside
 *			the IPv6 header.
 *		**BPF_LWT_ENCAP_IP**
 *			IP encapsulation (GRE/GUE/IPIP/etc). The outer header
 *			must be IPv4 or IPv6, followed by zero or more
 *			additional headers, up to **LWT_BPF_MAX_HEADROOM**
 *			total bytes in all prepended headers. Please note that
 *			अगर **skb_is_gso**\ (*skb*) is true, no more than two
 *			headers can be prepended, and the inner header, अगर
 *			present, should be either GRE or UDP/GUE.
 *
 *		**BPF_LWT_ENCAP_SEG6**\ \* types can be called by BPF programs
 *		of type **BPF_PROG_TYPE_LWT_IN**; **BPF_LWT_ENCAP_IP** type can
 *		be called by bpf programs of types **BPF_PROG_TYPE_LWT_IN** and
 *		**BPF_PROG_TYPE_LWT_XMIT**.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 *	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_lwt_seg6_store_bytes(काष्ठा sk_buff *skb, u32 offset, स्थिर व्योम *from, u32 len)
 *	Description
 *		Store *len* bytes from address *from* पूर्णांकo the packet
 *		associated to *skb*, at *offset*. Only the flags, tag and TLVs
 *		inside the outermost IPv6 Segment Routing Header can be
 *		modअगरied through this helper.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 *	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_lwt_seg6_adjust_srh(काष्ठा sk_buff *skb, u32 offset, s32 delta)
 *	Description
 *		Adjust the size allocated to TLVs in the outermost IPv6
 *		Segment Routing Header contained in the packet associated to
 *		*skb*, at position *offset* by *delta* bytes. Only offsets
 *		after the segments are accepted. *delta* can be as well
 *		positive (growing) as negative (shrinking).
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 *	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_lwt_seg6_action(काष्ठा sk_buff *skb, u32 action, व्योम *param, u32 param_len)
 *	Description
 *		Apply an IPv6 Segment Routing action of type *action* to the
 *		packet associated to *skb*. Each action takes a parameter
 *		contained at address *param*, and of length *param_len* bytes.
 *		*action* can be one of:
 *
 *		**SEG6_LOCAL_ACTION_END_X**
 *			End.X action: Endpoपूर्णांक with Layer-3 cross-connect.
 *			Type of *param*: **काष्ठा in6_addr**.
 *		**SEG6_LOCAL_ACTION_END_T**
 *			End.T action: Endpoपूर्णांक with specअगरic IPv6 table lookup.
 *			Type of *param*: **पूर्णांक**.
 *		**SEG6_LOCAL_ACTION_END_B6**
 *			End.B6 action: Endpoपूर्णांक bound to an SRv6 policy.
 *			Type of *param*: **काष्ठा ipv6_sr_hdr**.
 *		**SEG6_LOCAL_ACTION_END_B6_ENCAP**
 *			End.B6.Encap action: Endpoपूर्णांक bound to an SRv6
 *			encapsulation policy.
 *			Type of *param*: **काष्ठा ipv6_sr_hdr**.
 *
 * 		A call to this helper is susceptible to change the underlying
 * 		packet buffer. Thereक्रमe, at load समय, all checks on poपूर्णांकers
 * 		previously करोne by the verअगरier are invalidated and must be
 * 		perक्रमmed again, अगर the helper is used in combination with
 * 		direct packet access.
 *	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_rc_repeat(व्योम *ctx)
 *	Description
 *		This helper is used in programs implementing IR decoding, to
 *		report a successfully decoded repeat key message. This delays
 *		the generation of a key up event क्रम previously generated
 *		key करोwn event.
 *
 *		Some IR protocols like NEC have a special IR message क्रम
 *		repeating last button, क्रम when a button is held करोwn.
 *
 *		The *ctx* should poपूर्णांक to the lirc sample as passed पूर्णांकo
 *		the program.
 *
 *		This helper is only available is the kernel was compiled with
 *		the **CONFIG_BPF_LIRC_MODE2** configuration option set to
 *		"**y**".
 *	Return
 *		0
 *
 * दीर्घ bpf_rc_keyकरोwn(व्योम *ctx, u32 protocol, u64 scancode, u32 toggle)
 *	Description
 *		This helper is used in programs implementing IR decoding, to
 *		report a successfully decoded key press with *scancode*,
 *		*toggle* value in the given *protocol*. The scancode will be
 *		translated to a keycode using the rc keymap, and reported as
 *		an input key करोwn event. After a period a key up event is
 *		generated. This period can be extended by calling either
 *		**bpf_rc_keyकरोwn**\ () again with the same values, or calling
 *		**bpf_rc_repeat**\ ().
 *
 *		Some protocols include a toggle bit, in हाल the button was
 *		released and pressed again between consecutive scancodes.
 *
 *		The *ctx* should poपूर्णांक to the lirc sample as passed पूर्णांकo
 *		the program.
 *
 *		The *protocol* is the decoded protocol number (see
 *		**क्रमागत rc_proto** क्रम some predefined values).
 *
 *		This helper is only available is the kernel was compiled with
 *		the **CONFIG_BPF_LIRC_MODE2** configuration option set to
 *		"**y**".
 *	Return
 *		0
 *
 * u64 bpf_skb_cgroup_id(काष्ठा sk_buff *skb)
 * 	Description
 * 		Return the cgroup v2 id of the socket associated with the *skb*.
 * 		This is roughly similar to the **bpf_get_cgroup_classid**\ ()
 * 		helper क्रम cgroup v1 by providing a tag resp. identअगरier that
 * 		can be matched on or used क्रम map lookups e.g. to implement
 * 		policy. The cgroup v2 id of a given path in the hierarchy is
 * 		exposed in user space through the f_handle API in order to get
 * 		to the same 64-bit id.
 *
 * 		This helper can be used on TC egress path, but not on ingress,
 * 		and is available only अगर the kernel was compiled with the
 * 		**CONFIG_SOCK_CGROUP_DATA** configuration option.
 * 	Return
 * 		The id is वापसed or 0 in हाल the id could not be retrieved.
 *
 * u64 bpf_get_current_cgroup_id(व्योम)
 * 	Return
 * 		A 64-bit पूर्णांकeger containing the current cgroup id based
 * 		on the cgroup within which the current task is running.
 *
 * व्योम *bpf_get_local_storage(व्योम *map, u64 flags)
 *	Description
 *		Get the poपूर्णांकer to the local storage area.
 *		The type and the size of the local storage is defined
 *		by the *map* argument.
 *		The *flags* meaning is specअगरic क्रम each map type,
 *		and has to be 0 क्रम cgroup local storage.
 *
 *		Depending on the BPF program type, a local storage area
 *		can be shared between multiple instances of the BPF program,
 *		running simultaneously.
 *
 *		A user should care about the synchronization by himself.
 *		For example, by using the **BPF_ATOMIC** inकाष्ठाions to alter
 *		the shared data.
 *	Return
 *		A poपूर्णांकer to the local storage area.
 *
 * दीर्घ bpf_sk_select_reuseport(काष्ठा sk_reuseport_md *reuse, काष्ठा bpf_map *map, व्योम *key, u64 flags)
 *	Description
 *		Select a **SO_REUSEPORT** socket from a
 *		**BPF_MAP_TYPE_REUSEPORT_ARRAY** *map*.
 *		It checks the selected socket is matching the incoming
 *		request in the socket buffer.
 *	Return
 *		0 on success, or a negative error in हाल of failure.
 *
 * u64 bpf_skb_ancestor_cgroup_id(काष्ठा sk_buff *skb, पूर्णांक ancestor_level)
 *	Description
 *		Return id of cgroup v2 that is ancestor of cgroup associated
 *		with the *skb* at the *ancestor_level*.  The root cgroup is at
 *		*ancestor_level* zero and each step करोwn the hierarchy
 *		increments the level. If *ancestor_level* == level of cgroup
 *		associated with *skb*, then वापस value will be same as that
 *		of **bpf_skb_cgroup_id**\ ().
 *
 *		The helper is useful to implement policies based on cgroups
 *		that are upper in hierarchy than immediate cgroup associated
 *		with *skb*.
 *
 *		The क्रमmat of वापसed id and helper limitations are same as in
 *		**bpf_skb_cgroup_id**\ ().
 *	Return
 *		The id is वापसed or 0 in हाल the id could not be retrieved.
 *
 * काष्ठा bpf_sock *bpf_sk_lookup_tcp(व्योम *ctx, काष्ठा bpf_sock_tuple *tuple, u32 tuple_size, u64 netns, u64 flags)
 *	Description
 *		Look क्रम TCP socket matching *tuple*, optionally in a child
 *		network namespace *netns*. The वापस value must be checked,
 *		and अगर non-**शून्य**, released via **bpf_sk_release**\ ().
 *
 *		The *ctx* should poपूर्णांक to the context of the program, such as
 *		the skb or socket (depending on the hook in use). This is used
 *		to determine the base network namespace क्रम the lookup.
 *
 *		*tuple_size* must be one of:
 *
 *		**माप**\ (*tuple*\ **->ipv4**)
 *			Look क्रम an IPv4 socket.
 *		**माप**\ (*tuple*\ **->ipv6**)
 *			Look क्रम an IPv6 socket.
 *
 *		If the *netns* is a negative चिन्हित 32-bit पूर्णांकeger, then the
 *		socket lookup table in the netns associated with the *ctx*
 *		will be used. For the TC hooks, this is the netns of the device
 *		in the skb. For socket hooks, this is the netns of the socket.
 *		If *netns* is any other चिन्हित 32-bit value greater than or
 *		equal to zero then it specअगरies the ID of the netns relative to
 *		the netns associated with the *ctx*. *netns* values beyond the
 *		range of 32-bit पूर्णांकegers are reserved क्रम future use.
 *
 *		All values क्रम *flags* are reserved क्रम future usage, and must
 *		be left at zero.
 *
 *		This helper is available only अगर the kernel was compiled with
 *		**CONFIG_NET** configuration option.
 *	Return
 *		Poपूर्णांकer to **काष्ठा bpf_sock**, or **शून्य** in हाल of failure.
 *		For sockets with reuseport option, the **काष्ठा bpf_sock**
 *		result is from *reuse*\ **->socks**\ [] using the hash of the
 *		tuple.
 *
 * काष्ठा bpf_sock *bpf_sk_lookup_udp(व्योम *ctx, काष्ठा bpf_sock_tuple *tuple, u32 tuple_size, u64 netns, u64 flags)
 *	Description
 *		Look क्रम UDP socket matching *tuple*, optionally in a child
 *		network namespace *netns*. The वापस value must be checked,
 *		and अगर non-**शून्य**, released via **bpf_sk_release**\ ().
 *
 *		The *ctx* should poपूर्णांक to the context of the program, such as
 *		the skb or socket (depending on the hook in use). This is used
 *		to determine the base network namespace क्रम the lookup.
 *
 *		*tuple_size* must be one of:
 *
 *		**माप**\ (*tuple*\ **->ipv4**)
 *			Look क्रम an IPv4 socket.
 *		**माप**\ (*tuple*\ **->ipv6**)
 *			Look क्रम an IPv6 socket.
 *
 *		If the *netns* is a negative चिन्हित 32-bit पूर्णांकeger, then the
 *		socket lookup table in the netns associated with the *ctx*
 *		will be used. For the TC hooks, this is the netns of the device
 *		in the skb. For socket hooks, this is the netns of the socket.
 *		If *netns* is any other चिन्हित 32-bit value greater than or
 *		equal to zero then it specअगरies the ID of the netns relative to
 *		the netns associated with the *ctx*. *netns* values beyond the
 *		range of 32-bit पूर्णांकegers are reserved क्रम future use.
 *
 *		All values क्रम *flags* are reserved क्रम future usage, and must
 *		be left at zero.
 *
 *		This helper is available only अगर the kernel was compiled with
 *		**CONFIG_NET** configuration option.
 *	Return
 *		Poपूर्णांकer to **काष्ठा bpf_sock**, or **शून्य** in हाल of failure.
 *		For sockets with reuseport option, the **काष्ठा bpf_sock**
 *		result is from *reuse*\ **->socks**\ [] using the hash of the
 *		tuple.
 *
 * दीर्घ bpf_sk_release(व्योम *sock)
 *	Description
 *		Release the reference held by *sock*. *sock* must be a
 *		non-**शून्य** poपूर्णांकer that was वापसed from
 *		**bpf_sk_lookup_xxx**\ ().
 *	Return
 *		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_map_push_elem(काष्ठा bpf_map *map, स्थिर व्योम *value, u64 flags)
 * 	Description
 * 		Push an element *value* in *map*. *flags* is one of:
 *
 * 		**BPF_EXIST**
 * 			If the queue/stack is full, the oldest element is
 * 			हटाओd to make room क्रम this.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_map_pop_elem(काष्ठा bpf_map *map, व्योम *value)
 * 	Description
 * 		Pop an element from *map*.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_map_peek_elem(काष्ठा bpf_map *map, व्योम *value)
 * 	Description
 * 		Get an element from *map* without removing it.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_msg_push_data(काष्ठा sk_msg_buff *msg, u32 start, u32 len, u64 flags)
 *	Description
 *		For socket policies, insert *len* bytes पूर्णांकo *msg* at offset
 *		*start*.
 *
 *		If a program of type **BPF_PROG_TYPE_SK_MSG** is run on a
 *		*msg* it may want to insert metadata or options पूर्णांकo the *msg*.
 *		This can later be पढ़ो and used by any of the lower layer BPF
 *		hooks.
 *
 *		This helper may fail अगर under memory pressure (a दो_स्मृति
 *		fails) in these हालs BPF programs will get an appropriate
 *		error and BPF programs will need to handle them.
 *	Return
 *		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_msg_pop_data(काष्ठा sk_msg_buff *msg, u32 start, u32 len, u64 flags)
 *	Description
 *		Will हटाओ *len* bytes from a *msg* starting at byte *start*.
 *		This may result in **ENOMEM** errors under certain situations अगर
 *		an allocation and copy are required due to a full ring buffer.
 *		However, the helper will try to aव्योम करोing the allocation
 *		अगर possible. Other errors can occur अगर input parameters are
 *		invalid either due to *start* byte not being valid part of *msg*
 *		payload and/or *pop* value being to large.
 *	Return
 *		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_rc_poपूर्णांकer_rel(व्योम *ctx, s32 rel_x, s32 rel_y)
 *	Description
 *		This helper is used in programs implementing IR decoding, to
 *		report a successfully decoded poपूर्णांकer movement.
 *
 *		The *ctx* should poपूर्णांक to the lirc sample as passed पूर्णांकo
 *		the program.
 *
 *		This helper is only available is the kernel was compiled with
 *		the **CONFIG_BPF_LIRC_MODE2** configuration option set to
 *		"**y**".
 *	Return
 *		0
 *
 * दीर्घ bpf_spin_lock(काष्ठा bpf_spin_lock *lock)
 *	Description
 *		Acquire a spinlock represented by the poपूर्णांकer *lock*, which is
 *		stored as part of a value of a map. Taking the lock allows to
 *		safely update the rest of the fields in that value. The
 *		spinlock can (and must) later be released with a call to
 *		**bpf_spin_unlock**\ (\ *lock*\ ).
 *
 *		Spinlocks in BPF programs come with a number of restrictions
 *		and स्थिरraपूर्णांकs:
 *
 *		* **bpf_spin_lock** objects are only allowed inside maps of
 *		  types **BPF_MAP_TYPE_HASH** and **BPF_MAP_TYPE_ARRAY** (this
 *		  list could be extended in the future).
 *		* BTF description of the map is mandatory.
 *		* The BPF program can take ONE lock at a समय, since taking two
 *		  or more could cause dead locks.
 *		* Only one **काष्ठा bpf_spin_lock** is allowed per map element.
 *		* When the lock is taken, calls (either BPF to BPF or helpers)
 *		  are not allowed.
 *		* The **BPF_LD_ABS** and **BPF_LD_IND** inकाष्ठाions are not
 *		  allowed inside a spinlock-ed region.
 *		* The BPF program MUST call **bpf_spin_unlock**\ () to release
 *		  the lock, on all execution paths, beक्रमe it वापसs.
 *		* The BPF program can access **काष्ठा bpf_spin_lock** only via
 *		  the **bpf_spin_lock**\ () and **bpf_spin_unlock**\ ()
 *		  helpers. Loading or storing data पूर्णांकo the **काष्ठा
 *		  bpf_spin_lock** *lock*\ **;** field of a map is not allowed.
 *		* To use the **bpf_spin_lock**\ () helper, the BTF description
 *		  of the map value must be a काष्ठा and have **काष्ठा
 *		  bpf_spin_lock** *anyname*\ **;** field at the top level.
 *		  Nested lock inside another काष्ठा is not allowed.
 *		* The **काष्ठा bpf_spin_lock** *lock* field in a map value must
 *		  be aligned on a multiple of 4 bytes in that value.
 *		* Syscall with command **BPF_MAP_LOOKUP_ELEM** करोes not copy
 *		  the **bpf_spin_lock** field to user space.
 *		* Syscall with command **BPF_MAP_UPDATE_ELEM**, or update from
 *		  a BPF program, करो not update the **bpf_spin_lock** field.
 *		* **bpf_spin_lock** cannot be on the stack or inside a
 *		  networking packet (it can only be inside of a map values).
 *		* **bpf_spin_lock** is available to root only.
 *		* Tracing programs and socket filter programs cannot use
 *		  **bpf_spin_lock**\ () due to insufficient preemption checks
 *		  (but this may change in the future).
 *		* **bpf_spin_lock** is not allowed in inner maps of map-in-map.
 *	Return
 *		0
 *
 * दीर्घ bpf_spin_unlock(काष्ठा bpf_spin_lock *lock)
 *	Description
 *		Release the *lock* previously locked by a call to
 *		**bpf_spin_lock**\ (\ *lock*\ ).
 *	Return
 *		0
 *
 * काष्ठा bpf_sock *bpf_sk_fullsock(काष्ठा bpf_sock *sk)
 *	Description
 *		This helper माला_लो a **काष्ठा bpf_sock** poपूर्णांकer such
 *		that all the fields in this **bpf_sock** can be accessed.
 *	Return
 *		A **काष्ठा bpf_sock** poपूर्णांकer on success, or **शून्य** in
 *		हाल of failure.
 *
 * काष्ठा bpf_tcp_sock *bpf_tcp_sock(काष्ठा bpf_sock *sk)
 *	Description
 *		This helper माला_लो a **काष्ठा bpf_tcp_sock** poपूर्णांकer from a
 *		**काष्ठा bpf_sock** poपूर्णांकer.
 *	Return
 *		A **काष्ठा bpf_tcp_sock** poपूर्णांकer on success, or **शून्य** in
 *		हाल of failure.
 *
 * दीर्घ bpf_skb_ecn_set_ce(काष्ठा sk_buff *skb)
 *	Description
 *		Set ECN (Explicit Congestion Notअगरication) field of IP header
 *		to **CE** (Congestion Encountered) अगर current value is **ECT**
 *		(ECN Capable Transport). Otherwise, करो nothing. Works with IPv6
 *		and IPv4.
 *	Return
 *		1 अगर the **CE** flag is set (either by the current helper call
 *		or because it was alपढ़ोy present), 0 अगर it is not set.
 *
 * काष्ठा bpf_sock *bpf_get_listener_sock(काष्ठा bpf_sock *sk)
 *	Description
 *		Return a **काष्ठा bpf_sock** poपूर्णांकer in **TCP_LISTEN** state.
 *		**bpf_sk_release**\ () is unnecessary and not allowed.
 *	Return
 *		A **काष्ठा bpf_sock** poपूर्णांकer on success, or **शून्य** in
 *		हाल of failure.
 *
 * काष्ठा bpf_sock *bpf_skc_lookup_tcp(व्योम *ctx, काष्ठा bpf_sock_tuple *tuple, u32 tuple_size, u64 netns, u64 flags)
 *	Description
 *		Look क्रम TCP socket matching *tuple*, optionally in a child
 *		network namespace *netns*. The वापस value must be checked,
 *		and अगर non-**शून्य**, released via **bpf_sk_release**\ ().
 *
 *		This function is identical to **bpf_sk_lookup_tcp**\ (), except
 *		that it also वापसs समयरुको or request sockets. Use
 *		**bpf_sk_fullsock**\ () or **bpf_tcp_sock**\ () to access the
 *		full काष्ठाure.
 *
 *		This helper is available only अगर the kernel was compiled with
 *		**CONFIG_NET** configuration option.
 *	Return
 *		Poपूर्णांकer to **काष्ठा bpf_sock**, or **शून्य** in हाल of failure.
 *		For sockets with reuseport option, the **काष्ठा bpf_sock**
 *		result is from *reuse*\ **->socks**\ [] using the hash of the
 *		tuple.
 *
 * दीर्घ bpf_tcp_check_syncookie(व्योम *sk, व्योम *iph, u32 iph_len, काष्ठा tcphdr *th, u32 th_len)
 * 	Description
 * 		Check whether *iph* and *th* contain a valid SYN cookie ACK क्रम
 * 		the listening socket in *sk*.
 *
 * 		*iph* poपूर्णांकs to the start of the IPv4 or IPv6 header, जबतक
 * 		*iph_len* contains **माप**\ (**काष्ठा iphdr**) or
 * 		**माप**\ (**काष्ठा ip6hdr**).
 *
 * 		*th* poपूर्णांकs to the start of the TCP header, जबतक *th_len*
 * 		contains **माप**\ (**काष्ठा tcphdr**).
 * 	Return
 * 		0 अगर *iph* and *th* are a valid SYN cookie ACK, or a negative
 * 		error otherwise.
 *
 * दीर्घ bpf_sysctl_get_name(काष्ठा bpf_sysctl *ctx, अक्षर *buf, माप_प्रकार buf_len, u64 flags)
 *	Description
 *		Get name of sysctl in /proc/sys/ and copy it पूर्णांकo provided by
 *		program buffer *buf* of size *buf_len*.
 *
 *		The buffer is always NUL terminated, unless it's zero-sized.
 *
 *		If *flags* is zero, full name (e.g. "net/ipv4/tcp_mem") is
 *		copied. Use **BPF_F_SYSCTL_BASE_NAME** flag to copy base name
 *		only (e.g. "tcp_mem").
 *	Return
 *		Number of अक्षरacter copied (not including the trailing NUL).
 *
 *		**-E2BIG** अगर the buffer wasn't big enough (*buf* will contain
 *		truncated name in this हाल).
 *
 * दीर्घ bpf_sysctl_get_current_value(काष्ठा bpf_sysctl *ctx, अक्षर *buf, माप_प्रकार buf_len)
 *	Description
 *		Get current value of sysctl as it is presented in /proc/sys
 *		(incl. newline, etc), and copy it as a string पूर्णांकo provided
 *		by program buffer *buf* of size *buf_len*.
 *
 *		The whole value is copied, no matter what file position user
 *		space issued e.g. sys_पढ़ो at.
 *
 *		The buffer is always NUL terminated, unless it's zero-sized.
 *	Return
 *		Number of अक्षरacter copied (not including the trailing NUL).
 *
 *		**-E2BIG** अगर the buffer wasn't big enough (*buf* will contain
 *		truncated name in this हाल).
 *
 *		**-EINVAL** अगर current value was unavailable, e.g. because
 *		sysctl is uninitialized and पढ़ो वापसs -EIO क्रम it.
 *
 * दीर्घ bpf_sysctl_get_new_value(काष्ठा bpf_sysctl *ctx, अक्षर *buf, माप_प्रकार buf_len)
 *	Description
 *		Get new value being written by user space to sysctl (beक्रमe
 *		the actual ग_लिखो happens) and copy it as a string पूर्णांकo
 *		provided by program buffer *buf* of size *buf_len*.
 *
 *		User space may ग_लिखो new value at file position > 0.
 *
 *		The buffer is always NUL terminated, unless it's zero-sized.
 *	Return
 *		Number of अक्षरacter copied (not including the trailing NUL).
 *
 *		**-E2BIG** अगर the buffer wasn't big enough (*buf* will contain
 *		truncated name in this हाल).
 *
 *		**-EINVAL** अगर sysctl is being पढ़ो.
 *
 * दीर्घ bpf_sysctl_set_new_value(काष्ठा bpf_sysctl *ctx, स्थिर अक्षर *buf, माप_प्रकार buf_len)
 *	Description
 *		Override new value being written by user space to sysctl with
 *		value provided by program in buffer *buf* of size *buf_len*.
 *
 *		*buf* should contain a string in same क्रमm as provided by user
 *		space on sysctl ग_लिखो.
 *
 *		User space may ग_लिखो new value at file position > 0. To override
 *		the whole sysctl value file position should be set to zero.
 *	Return
 *		0 on success.
 *
 *		**-E2BIG** अगर the *buf_len* is too big.
 *
 *		**-EINVAL** अगर sysctl is being पढ़ो.
 *
 * दीर्घ bpf_म_से_दीर्घ(स्थिर अक्षर *buf, माप_प्रकार buf_len, u64 flags, दीर्घ *res)
 *	Description
 *		Convert the initial part of the string from buffer *buf* of
 *		size *buf_len* to a दीर्घ पूर्णांकeger according to the given base
 *		and save the result in *res*.
 *
 *		The string may begin with an arbitrary amount of white space
 *		(as determined by **है_खाली**\ (3)) followed by a single
 *		optional '**-**' sign.
 *
 *		Five least signअगरicant bits of *flags* encode base, other bits
 *		are currently unused.
 *
 *		Base must be either 8, 10, 16 or 0 to detect it स्वतःmatically
 *		similar to user space **म_से_दीर्घ**\ (3).
 *	Return
 *		Number of अक्षरacters consumed on success. Must be positive but
 *		no more than *buf_len*.
 *
 *		**-EINVAL** अगर no valid digits were found or unsupported base
 *		was provided.
 *
 *		**-दुस्फल** अगर resulting value was out of range.
 *
 * दीर्घ bpf_म_से_अदीर्घ(स्थिर अक्षर *buf, माप_प्रकार buf_len, u64 flags, अचिन्हित दीर्घ *res)
 *	Description
 *		Convert the initial part of the string from buffer *buf* of
 *		size *buf_len* to an अचिन्हित दीर्घ पूर्णांकeger according to the
 *		given base and save the result in *res*.
 *
 *		The string may begin with an arbitrary amount of white space
 *		(as determined by **है_खाली**\ (3)).
 *
 *		Five least signअगरicant bits of *flags* encode base, other bits
 *		are currently unused.
 *
 *		Base must be either 8, 10, 16 or 0 to detect it स्वतःmatically
 *		similar to user space **म_से_अदीर्घ**\ (3).
 *	Return
 *		Number of अक्षरacters consumed on success. Must be positive but
 *		no more than *buf_len*.
 *
 *		**-EINVAL** अगर no valid digits were found or unsupported base
 *		was provided.
 *
 *		**-दुस्फल** अगर resulting value was out of range.
 *
 * व्योम *bpf_sk_storage_get(काष्ठा bpf_map *map, व्योम *sk, व्योम *value, u64 flags)
 *	Description
 *		Get a bpf-local-storage from a *sk*.
 *
 *		Logically, it could be thought of getting the value from
 *		a *map* with *sk* as the **key**.  From this
 *		perspective,  the usage is not much dअगरferent from
 *		**bpf_map_lookup_elem**\ (*map*, **&**\ *sk*) except this
 *		helper enक्रमces the key must be a full socket and the map must
 *		be a **BPF_MAP_TYPE_SK_STORAGE** also.
 *
 *		Underneath, the value is stored locally at *sk* instead of
 *		the *map*.  The *map* is used as the bpf-local-storage
 *		"type". The bpf-local-storage "type" (i.e. the *map*) is
 *		searched against all bpf-local-storages residing at *sk*.
 *
 *		*sk* is a kernel **काष्ठा sock** poपूर्णांकer क्रम LSM program.
 *		*sk* is a **काष्ठा bpf_sock** poपूर्णांकer क्रम other program types.
 *
 *		An optional *flags* (**BPF_SK_STORAGE_GET_F_CREATE**) can be
 *		used such that a new bpf-local-storage will be
 *		created अगर one करोes not exist.  *value* can be used
 *		together with **BPF_SK_STORAGE_GET_F_CREATE** to specअगरy
 *		the initial value of a bpf-local-storage.  If *value* is
 *		**शून्य**, the new bpf-local-storage will be zero initialized.
 *	Return
 *		A bpf-local-storage poपूर्णांकer is वापसed on success.
 *
 *		**शून्य** अगर not found or there was an error in adding
 *		a new bpf-local-storage.
 *
 * दीर्घ bpf_sk_storage_delete(काष्ठा bpf_map *map, व्योम *sk)
 *	Description
 *		Delete a bpf-local-storage from a *sk*.
 *	Return
 *		0 on success.
 *
 *		**-ENOENT** अगर the bpf-local-storage cannot be found.
 *		**-EINVAL** अगर sk is not a fullsock (e.g. a request_sock).
 *
 * दीर्घ bpf_send_संकेत(u32 sig)
 *	Description
 *		Send संकेत *sig* to the process of the current task.
 *		The संकेत may be delivered to any of this process's thपढ़ोs.
 *	Return
 *		0 on success or successfully queued.
 *
 *		**-EBUSY** अगर work queue under nmi is full.
 *
 *		**-EINVAL** अगर *sig* is invalid.
 *
 *		**-EPERM** अगर no permission to send the *sig*.
 *
 *		**-EAGAIN** अगर bpf program can try again.
 *
 * s64 bpf_tcp_gen_syncookie(व्योम *sk, व्योम *iph, u32 iph_len, काष्ठा tcphdr *th, u32 th_len)
 *	Description
 *		Try to issue a SYN cookie क्रम the packet with corresponding
 *		IP/TCP headers, *iph* and *th*, on the listening socket in *sk*.
 *
 *		*iph* poपूर्णांकs to the start of the IPv4 or IPv6 header, जबतक
 *		*iph_len* contains **माप**\ (**काष्ठा iphdr**) or
 *		**माप**\ (**काष्ठा ip6hdr**).
 *
 *		*th* poपूर्णांकs to the start of the TCP header, जबतक *th_len*
 *		contains the length of the TCP header.
 *	Return
 *		On success, lower 32 bits hold the generated SYN cookie in
 *		followed by 16 bits which hold the MSS value क्रम that cookie,
 *		and the top 16 bits are unused.
 *
 *		On failure, the वापसed value is one of the following:
 *
 *		**-EINVAL** SYN cookie cannot be issued due to error
 *
 *		**-ENOENT** SYN cookie should not be issued (no SYN flood)
 *
 *		**-EOPNOTSUPP** kernel configuration करोes not enable SYN cookies
 *
 *		**-EPROTONOSUPPORT** IP packet version is not 4 or 6
 *
 * दीर्घ bpf_skb_output(व्योम *ctx, काष्ठा bpf_map *map, u64 flags, व्योम *data, u64 size)
 * 	Description
 * 		Write raw *data* blob पूर्णांकo a special BPF perf event held by
 * 		*map* of type **BPF_MAP_TYPE_PERF_EVENT_ARRAY**. This perf
 * 		event must have the following attributes: **PERF_SAMPLE_RAW**
 * 		as **sample_type**, **PERF_TYPE_SOFTWARE** as **type**, and
 * 		**PERF_COUNT_SW_BPF_OUTPUT** as **config**.
 *
 * 		The *flags* are used to indicate the index in *map* क्रम which
 * 		the value must be put, masked with **BPF_F_INDEX_MASK**.
 * 		Alternatively, *flags* can be set to **BPF_F_CURRENT_CPU**
 * 		to indicate that the index of the current CPU core should be
 * 		used.
 *
 * 		The value to ग_लिखो, of *size*, is passed through eBPF stack and
 * 		poपूर्णांकed by *data*.
 *
 * 		*ctx* is a poपूर्णांकer to in-kernel काष्ठा sk_buff.
 *
 * 		This helper is similar to **bpf_perf_event_output**\ () but
 * 		restricted to raw_tracepoपूर्णांक bpf programs.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_probe_पढ़ो_user(व्योम *dst, u32 size, स्थिर व्योम *unsafe_ptr)
 * 	Description
 * 		Safely attempt to पढ़ो *size* bytes from user space address
 * 		*unsafe_ptr* and store the data in *dst*.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_probe_पढ़ो_kernel(व्योम *dst, u32 size, स्थिर व्योम *unsafe_ptr)
 * 	Description
 * 		Safely attempt to पढ़ो *size* bytes from kernel space address
 * 		*unsafe_ptr* and store the data in *dst*.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_probe_पढ़ो_user_str(व्योम *dst, u32 size, स्थिर व्योम *unsafe_ptr)
 * 	Description
 * 		Copy a NUL terminated string from an unsafe user address
 * 		*unsafe_ptr* to *dst*. The *size* should include the
 * 		terminating NUL byte. In हाल the string length is smaller than
 * 		*size*, the target is not padded with further NUL bytes. If the
 * 		string length is larger than *size*, just *size*-1 bytes are
 * 		copied and the last byte is set to NUL.
 *
 * 		On success, वापसs the number of bytes that were written,
 * 		including the terminal NUL. This makes this helper useful in
 * 		tracing programs क्रम पढ़ोing strings, and more importantly to
 * 		get its length at runसमय. See the following snippet:
 *
 * 		::
 *
 * 			SEC("kprobe/sys_open")
 * 			व्योम bpf_sys_खोलो(काष्ठा pt_regs *ctx)
 * 			अणु
 * 			        अक्षर buf[PATHLEN]; // PATHLEN is defined to 256
 * 			        पूर्णांक res = bpf_probe_पढ़ो_user_str(buf, माप(buf),
 * 				                                  ctx->di);
 *
 * 				// Consume buf, क्रम example push it to
 * 				// userspace via bpf_perf_event_output(); we
 * 				// can use res (the string length) as event
 * 				// size, after checking its boundaries.
 * 			पूर्ण
 *
 * 		In comparison, using **bpf_probe_पढ़ो_user**\ () helper here
 * 		instead to पढ़ो the string would require to estimate the length
 * 		at compile समय, and would often result in copying more memory
 * 		than necessary.
 *
 * 		Another useful use हाल is when parsing inभागidual process
 * 		arguments or inभागidual environment variables navigating
 * 		*current*\ **->mm->arg_start** and *current*\
 * 		**->mm->env_start**: using this helper and the वापस value,
 * 		one can quickly iterate at the right offset of the memory area.
 * 	Return
 * 		On success, the strictly positive length of the output string,
 * 		including the trailing NUL अक्षरacter. On error, a negative
 * 		value.
 *
 * दीर्घ bpf_probe_पढ़ो_kernel_str(व्योम *dst, u32 size, स्थिर व्योम *unsafe_ptr)
 * 	Description
 * 		Copy a NUL terminated string from an unsafe kernel address *unsafe_ptr*
 * 		to *dst*. Same semantics as with **bpf_probe_पढ़ो_user_str**\ () apply.
 * 	Return
 * 		On success, the strictly positive length of the string, including
 * 		the trailing NUL अक्षरacter. On error, a negative value.
 *
 * दीर्घ bpf_tcp_send_ack(व्योम *tp, u32 rcv_nxt)
 *	Description
 *		Send out a tcp-ack. *tp* is the in-kernel काष्ठा **tcp_sock**.
 *		*rcv_nxt* is the ack_seq to be sent out.
 *	Return
 *		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_send_संकेत_thपढ़ो(u32 sig)
 *	Description
 *		Send संकेत *sig* to the thपढ़ो corresponding to the current task.
 *	Return
 *		0 on success or successfully queued.
 *
 *		**-EBUSY** अगर work queue under nmi is full.
 *
 *		**-EINVAL** अगर *sig* is invalid.
 *
 *		**-EPERM** अगर no permission to send the *sig*.
 *
 *		**-EAGAIN** अगर bpf program can try again.
 *
 * u64 bpf_jअगरfies64(व्योम)
 *	Description
 *		Obtain the 64bit jअगरfies
 *	Return
 *		The 64 bit jअगरfies
 *
 * दीर्घ bpf_पढ़ो_branch_records(काष्ठा bpf_perf_event_data *ctx, व्योम *buf, u32 size, u64 flags)
 *	Description
 *		For an eBPF program attached to a perf event, retrieve the
 *		branch records (**काष्ठा perf_branch_entry**) associated to *ctx*
 *		and store it in the buffer poपूर्णांकed by *buf* up to size
 *		*size* bytes.
 *	Return
 *		On success, number of bytes written to *buf*. On error, a
 *		negative value.
 *
 *		The *flags* can be set to **BPF_F_GET_BRANCH_RECORDS_SIZE** to
 *		instead वापस the number of bytes required to store all the
 *		branch entries. If this flag is set, *buf* may be शून्य.
 *
 *		**-EINVAL** अगर arguments invalid or **size** not a multiple
 *		of **माप**\ (**काष्ठा perf_branch_entry**\ ).
 *
 *		**-ENOENT** अगर architecture करोes not support branch records.
 *
 * दीर्घ bpf_get_ns_current_pid_tgid(u64 dev, u64 ino, काष्ठा bpf_pidns_info *nsdata, u32 size)
 *	Description
 *		Returns 0 on success, values क्रम *pid* and *tgid* as seen from the current
 *		*namespace* will be वापसed in *nsdata*.
 *	Return
 *		0 on success, or one of the following in हाल of failure:
 *
 *		**-EINVAL** अगर dev and inum supplied करोn't match dev_t and inode number
 *              with nsfs of current task, or अगर dev conversion to dev_t lost high bits.
 *
 *		**-ENOENT** अगर pidns करोes not exists क्रम the current task.
 *
 * दीर्घ bpf_xdp_output(व्योम *ctx, काष्ठा bpf_map *map, u64 flags, व्योम *data, u64 size)
 *	Description
 *		Write raw *data* blob पूर्णांकo a special BPF perf event held by
 *		*map* of type **BPF_MAP_TYPE_PERF_EVENT_ARRAY**. This perf
 *		event must have the following attributes: **PERF_SAMPLE_RAW**
 *		as **sample_type**, **PERF_TYPE_SOFTWARE** as **type**, and
 *		**PERF_COUNT_SW_BPF_OUTPUT** as **config**.
 *
 *		The *flags* are used to indicate the index in *map* क्रम which
 *		the value must be put, masked with **BPF_F_INDEX_MASK**.
 *		Alternatively, *flags* can be set to **BPF_F_CURRENT_CPU**
 *		to indicate that the index of the current CPU core should be
 *		used.
 *
 *		The value to ग_लिखो, of *size*, is passed through eBPF stack and
 *		poपूर्णांकed by *data*.
 *
 *		*ctx* is a poपूर्णांकer to in-kernel काष्ठा xdp_buff.
 *
 *		This helper is similar to **bpf_perf_eventoutput**\ () but
 *		restricted to raw_tracepoपूर्णांक bpf programs.
 *	Return
 *		0 on success, or a negative error in हाल of failure.
 *
 * u64 bpf_get_netns_cookie(व्योम *ctx)
 * 	Description
 * 		Retrieve the cookie (generated by the kernel) of the network
 * 		namespace the input *ctx* is associated with. The network
 * 		namespace cookie reमुख्यs stable क्रम its lअगरeसमय and provides
 * 		a global identअगरier that can be assumed unique. If *ctx* is
 * 		शून्य, then the helper वापसs the cookie क्रम the initial
 * 		network namespace. The cookie itself is very similar to that
 * 		of **bpf_get_socket_cookie**\ () helper, but क्रम network
 * 		namespaces instead of sockets.
 * 	Return
 * 		A 8-byte दीर्घ opaque number.
 *
 * u64 bpf_get_current_ancestor_cgroup_id(पूर्णांक ancestor_level)
 * 	Description
 * 		Return id of cgroup v2 that is ancestor of the cgroup associated
 * 		with the current task at the *ancestor_level*. The root cgroup
 * 		is at *ancestor_level* zero and each step करोwn the hierarchy
 * 		increments the level. If *ancestor_level* == level of cgroup
 * 		associated with the current task, then वापस value will be the
 * 		same as that of **bpf_get_current_cgroup_id**\ ().
 *
 * 		The helper is useful to implement policies based on cgroups
 * 		that are upper in hierarchy than immediate cgroup associated
 * 		with the current task.
 *
 * 		The क्रमmat of वापसed id and helper limitations are same as in
 * 		**bpf_get_current_cgroup_id**\ ().
 * 	Return
 * 		The id is वापसed or 0 in हाल the id could not be retrieved.
 *
 * दीर्घ bpf_sk_assign(काष्ठा sk_buff *skb, व्योम *sk, u64 flags)
 *	Description
 *		Helper is overloaded depending on BPF program type. This
 *		description applies to **BPF_PROG_TYPE_SCHED_CLS** and
 *		**BPF_PROG_TYPE_SCHED_ACT** programs.
 *
 *		Assign the *sk* to the *skb*. When combined with appropriate
 *		routing configuration to receive the packet towards the socket,
 *		will cause *skb* to be delivered to the specअगरied socket.
 *		Subsequent redirection of *skb* via  **bpf_redirect**\ (),
 *		**bpf_clone_redirect**\ () or other methods outside of BPF may
 *		पूर्णांकerfere with successful delivery to the socket.
 *
 *		This operation is only valid from TC ingress path.
 *
 *		The *flags* argument must be zero.
 *	Return
 *		0 on success, or a negative error in हाल of failure:
 *
 *		**-EINVAL** अगर specअगरied *flags* are not supported.
 *
 *		**-ENOENT** अगर the socket is unavailable क्रम assignment.
 *
 *		**-ENETUNREACH** अगर the socket is unreachable (wrong netns).
 *
 *		**-EOPNOTSUPP** अगर the operation is not supported, क्रम example
 *		a call from outside of TC ingress.
 *
 *		**-ESOCKTNOSUPPORT** अगर the socket type is not supported
 *		(reuseport).
 *
 * दीर्घ bpf_sk_assign(काष्ठा bpf_sk_lookup *ctx, काष्ठा bpf_sock *sk, u64 flags)
 *	Description
 *		Helper is overloaded depending on BPF program type. This
 *		description applies to **BPF_PROG_TYPE_SK_LOOKUP** programs.
 *
 *		Select the *sk* as a result of a socket lookup.
 *
 *		For the operation to succeed passed socket must be compatible
 *		with the packet description provided by the *ctx* object.
 *
 *		L4 protocol (**IPPROTO_TCP** or **IPPROTO_UDP**) must
 *		be an exact match. While IP family (**AF_INET** or
 *		**AF_INET6**) must be compatible, that is IPv6 sockets
 *		that are not v6-only can be selected क्रम IPv4 packets.
 *
 *		Only TCP listeners and UDP unconnected sockets can be
 *		selected. *sk* can also be शून्य to reset any previous
 *		selection.
 *
 *		*flags* argument can combination of following values:
 *
 *		* **BPF_SK_LOOKUP_F_REPLACE** to override the previous
 *		  socket selection, potentially करोne by a BPF program
 *		  that ran beक्रमe us.
 *
 *		* **BPF_SK_LOOKUP_F_NO_REUSEPORT** to skip
 *		  load-balancing within reuseport group क्रम the socket
 *		  being selected.
 *
 *		On success *ctx->sk* will poपूर्णांक to the selected socket.
 *
 *	Return
 *		0 on success, or a negative त्रुटि_सं in हाल of failure.
 *
 *		* **-EAFNOSUPPORT** अगर socket family (*sk->family*) is
 *		  not compatible with packet family (*ctx->family*).
 *
 *		* **-EEXIST** अगर socket has been alपढ़ोy selected,
 *		  potentially by another program, and
 *		  **BPF_SK_LOOKUP_F_REPLACE** flag was not specअगरied.
 *
 *		* **-EINVAL** अगर unsupported flags were specअगरied.
 *
 *		* **-EPROTOTYPE** अगर socket L4 protocol
 *		  (*sk->protocol*) करोesn't match packet protocol
 *		  (*ctx->protocol*).
 *
 *		* **-ESOCKTNOSUPPORT** अगर socket is not in allowed
 *		  state (TCP listening or UDP unconnected).
 *
 * u64 bpf_kसमय_get_boot_ns(व्योम)
 * 	Description
 * 		Return the समय elapsed since प्रणाली boot, in nanoseconds.
 * 		Does include the समय the प्रणाली was suspended.
 * 		See: **घड़ी_समय_लो**\ (**CLOCK_BOOTTIME**)
 * 	Return
 * 		Current *kसमय*.
 *
 * दीर्घ bpf_seq_म_लिखो(काष्ठा seq_file *m, स्थिर अक्षर *fmt, u32 fmt_size, स्थिर व्योम *data, u32 data_len)
 * 	Description
 * 		**bpf_seq_म_लिखो**\ () uses seq_file **seq_म_लिखो**\ () to prपूर्णांक
 * 		out the क्रमmat string.
 * 		The *m* represents the seq_file. The *fmt* and *fmt_size* are क्रम
 * 		the क्रमmat string itself. The *data* and *data_len* are क्रमmat string
 * 		arguments. The *data* are a **u64** array and corresponding क्रमmat string
 * 		values are stored in the array. For strings and poपूर्णांकers where poपूर्णांकees
 * 		are accessed, only the poपूर्णांकer values are stored in the *data* array.
 * 		The *data_len* is the size of *data* in bytes.
 *
 *		Formats **%s**, **%pअणुi,Iपूर्णअणु4,6पूर्ण** requires to पढ़ो kernel memory.
 *		Reading kernel memory may fail due to either invalid address or
 *		valid address but requiring a major memory fault. If पढ़ोing kernel memory
 *		fails, the string क्रम **%s** will be an empty string, and the ip
 *		address क्रम **%pअणुi,Iपूर्णअणु4,6पूर्ण** will be 0. Not वापसing error to
 *		bpf program is consistent with what **bpf_trace_prपूर्णांकk**\ () करोes क्रम now.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure:
 *
 *		**-EBUSY** अगर per-CPU memory copy buffer is busy, can try again
 *		by वापसing 1 from bpf program.
 *
 *		**-EINVAL** अगर arguments are invalid, or अगर *fmt* is invalid/unsupported.
 *
 *		**-E2BIG** अगर *fmt* contains too many क्रमmat specअगरiers.
 *
 *		**-EOVERFLOW** अगर an overflow happened: The same object will be tried again.
 *
 * दीर्घ bpf_seq_ग_लिखो(काष्ठा seq_file *m, स्थिर व्योम *data, u32 len)
 * 	Description
 * 		**bpf_seq_ग_लिखो**\ () uses seq_file **seq_ग_लिखो**\ () to ग_लिखो the data.
 * 		The *m* represents the seq_file. The *data* and *len* represent the
 * 		data to ग_लिखो in bytes.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure:
 *
 *		**-EOVERFLOW** अगर an overflow happened: The same object will be tried again.
 *
 * u64 bpf_sk_cgroup_id(व्योम *sk)
 *	Description
 *		Return the cgroup v2 id of the socket *sk*.
 *
 *		*sk* must be a non-**शून्य** poपूर्णांकer to a socket, e.g. one
 *		वापसed from **bpf_sk_lookup_xxx**\ (),
 *		**bpf_sk_fullsock**\ (), etc. The क्रमmat of वापसed id is
 *		same as in **bpf_skb_cgroup_id**\ ().
 *
 *		This helper is available only अगर the kernel was compiled with
 *		the **CONFIG_SOCK_CGROUP_DATA** configuration option.
 *	Return
 *		The id is वापसed or 0 in हाल the id could not be retrieved.
 *
 * u64 bpf_sk_ancestor_cgroup_id(व्योम *sk, पूर्णांक ancestor_level)
 *	Description
 *		Return id of cgroup v2 that is ancestor of cgroup associated
 *		with the *sk* at the *ancestor_level*.  The root cgroup is at
 *		*ancestor_level* zero and each step करोwn the hierarchy
 *		increments the level. If *ancestor_level* == level of cgroup
 *		associated with *sk*, then वापस value will be same as that
 *		of **bpf_sk_cgroup_id**\ ().
 *
 *		The helper is useful to implement policies based on cgroups
 *		that are upper in hierarchy than immediate cgroup associated
 *		with *sk*.
 *
 *		The क्रमmat of वापसed id and helper limitations are same as in
 *		**bpf_sk_cgroup_id**\ ().
 *	Return
 *		The id is वापसed or 0 in हाल the id could not be retrieved.
 *
 * दीर्घ bpf_ringbuf_output(व्योम *ringbuf, व्योम *data, u64 size, u64 flags)
 * 	Description
 * 		Copy *size* bytes from *data* पूर्णांकo a ring buffer *ringbuf*.
 * 		If **BPF_RB_NO_WAKEUP** is specअगरied in *flags*, no notअगरication
 * 		of new data availability is sent.
 * 		If **BPF_RB_FORCE_WAKEUP** is specअगरied in *flags*, notअगरication
 * 		of new data availability is sent unconditionally.
 * 		If **0** is specअगरied in *flags*, an adaptive notअगरication
 * 		of new data availability is sent.
 *
 * 		An adaptive notअगरication is a notअगरication sent whenever the user-space
 * 		process has caught up and consumed all available payloads. In हाल the user-space
 * 		process is still processing a previous payload, then no notअगरication is needed
 * 		as it will process the newly added payload स्वतःmatically.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * व्योम *bpf_ringbuf_reserve(व्योम *ringbuf, u64 size, u64 flags)
 * 	Description
 * 		Reserve *size* bytes of payload in a ring buffer *ringbuf*.
 * 		*flags* must be 0.
 * 	Return
 * 		Valid poपूर्णांकer with *size* bytes of memory available; शून्य,
 * 		otherwise.
 *
 * व्योम bpf_ringbuf_submit(व्योम *data, u64 flags)
 * 	Description
 * 		Submit reserved ring buffer sample, poपूर्णांकed to by *data*.
 * 		If **BPF_RB_NO_WAKEUP** is specअगरied in *flags*, no notअगरication
 * 		of new data availability is sent.
 * 		If **BPF_RB_FORCE_WAKEUP** is specअगरied in *flags*, notअगरication
 * 		of new data availability is sent unconditionally.
 * 		If **0** is specअगरied in *flags*, an adaptive notअगरication
 * 		of new data availability is sent.
 *
 * 		See 'bpf_ringbuf_output()' क्रम the definition of adaptive notअगरication.
 * 	Return
 * 		Nothing. Always succeeds.
 *
 * व्योम bpf_ringbuf_discard(व्योम *data, u64 flags)
 * 	Description
 * 		Discard reserved ring buffer sample, poपूर्णांकed to by *data*.
 * 		If **BPF_RB_NO_WAKEUP** is specअगरied in *flags*, no notअगरication
 * 		of new data availability is sent.
 * 		If **BPF_RB_FORCE_WAKEUP** is specअगरied in *flags*, notअगरication
 * 		of new data availability is sent unconditionally.
 * 		If **0** is specअगरied in *flags*, an adaptive notअगरication
 * 		of new data availability is sent.
 *
 * 		See 'bpf_ringbuf_output()' क्रम the definition of adaptive notअगरication.
 * 	Return
 * 		Nothing. Always succeeds.
 *
 * u64 bpf_ringbuf_query(व्योम *ringbuf, u64 flags)
 *	Description
 *		Query various अक्षरacteristics of provided ring buffer. What
 *		exactly is queries is determined by *flags*:
 *
 *		* **BPF_RB_AVAIL_DATA**: Amount of data not yet consumed.
 *		* **BPF_RB_RING_SIZE**: The size of ring buffer.
 *		* **BPF_RB_CONS_POS**: Consumer position (can wrap around).
 *		* **BPF_RB_PROD_POS**: Producer(s) position (can wrap around).
 *
 *		Data वापसed is just a momentary snapshot of actual values
 *		and could be inaccurate, so this facility should be used to
 *		घातer heuristics and क्रम reporting, not to make 100% correct
 *		calculation.
 *	Return
 *		Requested value, or 0, अगर *flags* are not recognized.
 *
 * दीर्घ bpf_csum_level(काष्ठा sk_buff *skb, u64 level)
 * 	Description
 * 		Change the skbs checksum level by one layer up or करोwn, or
 * 		reset it entirely to none in order to have the stack perक्रमm
 * 		checksum validation. The level is applicable to the following
 * 		protocols: TCP, UDP, GRE, SCTP, FCOE. For example, a decap of
 * 		| ETH | IP | UDP | GUE | IP | TCP | पूर्णांकo | ETH | IP | TCP |
 * 		through **bpf_skb_adjust_room**\ () helper with passing in
 * 		**BPF_F_ADJ_ROOM_NO_CSUM_RESET** flag would require one	call
 * 		to **bpf_csum_level**\ () with **BPF_CSUM_LEVEL_DEC** since
 * 		the UDP header is हटाओd. Similarly, an encap of the latter
 * 		पूर्णांकo the क्रमmer could be accompanied by a helper call to
 * 		**bpf_csum_level**\ () with **BPF_CSUM_LEVEL_INC** अगर the
 * 		skb is still पूर्णांकended to be processed in higher layers of the
 * 		stack instead of just egressing at tc.
 *
 * 		There are three supported level settings at this समय:
 *
 * 		* **BPF_CSUM_LEVEL_INC**: Increases skb->csum_level क्रम skbs
 * 		  with CHECKSUM_UNNECESSARY.
 * 		* **BPF_CSUM_LEVEL_DEC**: Decreases skb->csum_level क्रम skbs
 * 		  with CHECKSUM_UNNECESSARY.
 * 		* **BPF_CSUM_LEVEL_RESET**: Resets skb->csum_level to 0 and
 * 		  sets CHECKSUM_NONE to क्रमce checksum validation by the stack.
 * 		* **BPF_CSUM_LEVEL_QUERY**: No-op, वापसs the current
 * 		  skb->csum_level.
 * 	Return
 * 		0 on success, or a negative error in हाल of failure. In the
 * 		हाल of **BPF_CSUM_LEVEL_QUERY**, the current skb->csum_level
 * 		is वापसed or the error code -EACCES in हाल the skb is not
 * 		subject to CHECKSUM_UNNECESSARY.
 *
 * काष्ठा tcp6_sock *bpf_skc_to_tcp6_sock(व्योम *sk)
 *	Description
 *		Dynamically cast a *sk* poपूर्णांकer to a *tcp6_sock* poपूर्णांकer.
 *	Return
 *		*sk* अगर casting is valid, or **शून्य** otherwise.
 *
 * काष्ठा tcp_sock *bpf_skc_to_tcp_sock(व्योम *sk)
 *	Description
 *		Dynamically cast a *sk* poपूर्णांकer to a *tcp_sock* poपूर्णांकer.
 *	Return
 *		*sk* अगर casting is valid, or **शून्य** otherwise.
 *
 * काष्ठा tcp_समयरुको_sock *bpf_skc_to_tcp_समयरुको_sock(व्योम *sk)
 * 	Description
 *		Dynamically cast a *sk* poपूर्णांकer to a *tcp_समयरुको_sock* poपूर्णांकer.
 *	Return
 *		*sk* अगर casting is valid, or **शून्य** otherwise.
 *
 * काष्ठा tcp_request_sock *bpf_skc_to_tcp_request_sock(व्योम *sk)
 * 	Description
 *		Dynamically cast a *sk* poपूर्णांकer to a *tcp_request_sock* poपूर्णांकer.
 *	Return
 *		*sk* अगर casting is valid, or **शून्य** otherwise.
 *
 * काष्ठा udp6_sock *bpf_skc_to_udp6_sock(व्योम *sk)
 * 	Description
 *		Dynamically cast a *sk* poपूर्णांकer to a *udp6_sock* poपूर्णांकer.
 *	Return
 *		*sk* अगर casting is valid, or **शून्य** otherwise.
 *
 * दीर्घ bpf_get_task_stack(काष्ठा task_काष्ठा *task, व्योम *buf, u32 size, u64 flags)
 *	Description
 *		Return a user or a kernel stack in bpf program provided buffer.
 *		To achieve this, the helper needs *task*, which is a valid
 *		poपूर्णांकer to **काष्ठा task_काष्ठा**. To store the stacktrace, the
 *		bpf program provides *buf* with a nonnegative *size*.
 *
 *		The last argument, *flags*, holds the number of stack frames to
 *		skip (from 0 to 255), masked with
 *		**BPF_F_SKIP_FIELD_MASK**. The next bits can be used to set
 *		the following flags:
 *
 *		**BPF_F_USER_STACK**
 *			Collect a user space stack instead of a kernel stack.
 *		**BPF_F_USER_BUILD_ID**
 *			Collect buildid+offset instead of ips क्रम user stack,
 *			only valid अगर **BPF_F_USER_STACK** is also specअगरied.
 *
 *		**bpf_get_task_stack**\ () can collect up to
 *		**PERF_MAX_STACK_DEPTH** both kernel and user frames, subject
 *		to sufficient large buffer size. Note that
 *		this limit can be controlled with the **sysctl** program, and
 *		that it should be manually increased in order to profile दीर्घ
 *		user stacks (such as stacks क्रम Java programs). To करो so, use:
 *
 *		::
 *
 *			# sysctl kernel.perf_event_max_stack=<new value>
 *	Return
 *		A non-negative value equal to or less than *size* on success,
 *		or a negative error in हाल of failure.
 *
 * दीर्घ bpf_load_hdr_opt(काष्ठा bpf_sock_ops *skops, व्योम *searchby_res, u32 len, u64 flags)
 *	Description
 *		Load header option.  Support पढ़ोing a particular TCP header
 *		option क्रम bpf program (**BPF_PROG_TYPE_SOCK_OPS**).
 *
 *		If *flags* is 0, it will search the option from the
 *		*skops*\ **->skb_data**.  The comment in **काष्ठा bpf_sock_ops**
 *		has details on what skb_data contains under dअगरferent
 *		*skops*\ **->op**.
 *
 *		The first byte of the *searchby_res* specअगरies the
 *		kind that it wants to search.
 *
 *		If the searching kind is an experimental kind
 *		(i.e. 253 or 254 according to RFC6994).  It also
 *		needs to specअगरy the "magic" which is either
 *		2 bytes or 4 bytes.  It then also needs to
 *		specअगरy the size of the magic by using
 *		the 2nd byte which is "kind-length" of a TCP
 *		header option and the "kind-length" also
 *		includes the first 2 bytes "kind" and "kind-length"
 *		itself as a normal TCP header option also करोes.
 *
 *		For example, to search experimental kind 254 with
 *		2 byte magic 0xeB9F, the searchby_res should be
 *		[ 254, 4, 0xeB, 0x9F, 0, 0, .... 0 ].
 *
 *		To search क्रम the standard winकरोw scale option (3),
 *		the *searchby_res* should be [ 3, 0, 0, .... 0 ].
 *		Note, kind-length must be 0 क्रम regular option.
 *
 *		Searching क्रम No-Op (0) and End-of-Option-List (1) are
 *		not supported.
 *
 *		*len* must be at least 2 bytes which is the minimal size
 *		of a header option.
 *
 *		Supported flags:
 *
 *		* **BPF_LOAD_HDR_OPT_TCP_SYN** to search from the
 *		  saved_syn packet or the just-received syn packet.
 *
 *	Return
 *		> 0 when found, the header option is copied to *searchby_res*.
 *		The वापस value is the total length copied. On failure, a
 *		negative error code is वापसed:
 *
 *		**-EINVAL** अगर a parameter is invalid.
 *
 *		**-ENOMSG** अगर the option is not found.
 *
 *		**-ENOENT** अगर no syn packet is available when
 *		**BPF_LOAD_HDR_OPT_TCP_SYN** is used.
 *
 *		**-ENOSPC** अगर there is not enough space.  Only *len* number of
 *		bytes are copied.
 *
 *		**-EFAULT** on failure to parse the header options in the
 *		packet.
 *
 *		**-EPERM** अगर the helper cannot be used under the current
 *		*skops*\ **->op**.
 *
 * दीर्घ bpf_store_hdr_opt(काष्ठा bpf_sock_ops *skops, स्थिर व्योम *from, u32 len, u64 flags)
 *	Description
 *		Store header option.  The data will be copied
 *		from buffer *from* with length *len* to the TCP header.
 *
 *		The buffer *from* should have the whole option that
 *		includes the kind, kind-length, and the actual
 *		option data.  The *len* must be at least kind-length
 *		दीर्घ.  The kind-length करोes not have to be 4 byte
 *		aligned.  The kernel will take care of the padding
 *		and setting the 4 bytes aligned value to th->करोff.
 *
 *		This helper will check क्रम duplicated option
 *		by searching the same option in the outgoing skb.
 *
 *		This helper can only be called during
 *		**BPF_SOCK_OPS_WRITE_HDR_OPT_CB**.
 *
 *	Return
 *		0 on success, or negative error in हाल of failure:
 *
 *		**-EINVAL** If param is invalid.
 *
 *		**-ENOSPC** अगर there is not enough space in the header.
 *		Nothing has been written
 *
 *		**-EEXIST** अगर the option alपढ़ोy exists.
 *
 *		**-EFAULT** on failrue to parse the existing header options.
 *
 *		**-EPERM** अगर the helper cannot be used under the current
 *		*skops*\ **->op**.
 *
 * दीर्घ bpf_reserve_hdr_opt(काष्ठा bpf_sock_ops *skops, u32 len, u64 flags)
 *	Description
 *		Reserve *len* bytes क्रम the bpf header option.  The
 *		space will be used by **bpf_store_hdr_opt**\ () later in
 *		**BPF_SOCK_OPS_WRITE_HDR_OPT_CB**.
 *
 *		If **bpf_reserve_hdr_opt**\ () is called multiple बार,
 *		the total number of bytes will be reserved.
 *
 *		This helper can only be called during
 *		**BPF_SOCK_OPS_HDR_OPT_LEN_CB**.
 *
 *	Return
 *		0 on success, or negative error in हाल of failure:
 *
 *		**-EINVAL** अगर a parameter is invalid.
 *
 *		**-ENOSPC** अगर there is not enough space in the header.
 *
 *		**-EPERM** अगर the helper cannot be used under the current
 *		*skops*\ **->op**.
 *
 * व्योम *bpf_inode_storage_get(काष्ठा bpf_map *map, व्योम *inode, व्योम *value, u64 flags)
 *	Description
 *		Get a bpf_local_storage from an *inode*.
 *
 *		Logically, it could be thought of as getting the value from
 *		a *map* with *inode* as the **key**.  From this
 *		perspective,  the usage is not much dअगरferent from
 *		**bpf_map_lookup_elem**\ (*map*, **&**\ *inode*) except this
 *		helper enक्रमces the key must be an inode and the map must also
 *		be a **BPF_MAP_TYPE_INODE_STORAGE**.
 *
 *		Underneath, the value is stored locally at *inode* instead of
 *		the *map*.  The *map* is used as the bpf-local-storage
 *		"type". The bpf-local-storage "type" (i.e. the *map*) is
 *		searched against all bpf_local_storage residing at *inode*.
 *
 *		An optional *flags* (**BPF_LOCAL_STORAGE_GET_F_CREATE**) can be
 *		used such that a new bpf_local_storage will be
 *		created अगर one करोes not exist.  *value* can be used
 *		together with **BPF_LOCAL_STORAGE_GET_F_CREATE** to specअगरy
 *		the initial value of a bpf_local_storage.  If *value* is
 *		**शून्य**, the new bpf_local_storage will be zero initialized.
 *	Return
 *		A bpf_local_storage poपूर्णांकer is वापसed on success.
 *
 *		**शून्य** अगर not found or there was an error in adding
 *		a new bpf_local_storage.
 *
 * पूर्णांक bpf_inode_storage_delete(काष्ठा bpf_map *map, व्योम *inode)
 *	Description
 *		Delete a bpf_local_storage from an *inode*.
 *	Return
 *		0 on success.
 *
 *		**-ENOENT** अगर the bpf_local_storage cannot be found.
 *
 * दीर्घ bpf_d_path(काष्ठा path *path, अक्षर *buf, u32 sz)
 *	Description
 *		Return full path क्रम given **काष्ठा path** object, which
 *		needs to be the kernel BTF *path* object. The path is
 *		वापसed in the provided buffer *buf* of size *sz* and
 *		is zero terminated.
 *
 *	Return
 *		On success, the strictly positive length of the string,
 *		including the trailing NUL अक्षरacter. On error, a negative
 *		value.
 *
 * दीर्घ bpf_copy_from_user(व्योम *dst, u32 size, स्थिर व्योम *user_ptr)
 * 	Description
 * 		Read *size* bytes from user space address *user_ptr* and store
 * 		the data in *dst*. This is a wrapper of **copy_from_user**\ ().
 * 	Return
 * 		0 on success, or a negative error in हाल of failure.
 *
 * दीर्घ bpf_snम_लिखो_btf(अक्षर *str, u32 str_size, काष्ठा btf_ptr *ptr, u32 btf_ptr_size, u64 flags)
 *	Description
 *		Use BTF to store a string representation of *ptr*->ptr in *str*,
 *		using *ptr*->type_id.  This value should specअगरy the type
 *		that *ptr*->ptr poपूर्णांकs to. LLVM __builtin_btf_type_id(type, 1)
 *		can be used to look up vmlinux BTF type ids. Traversing the
 *		data काष्ठाure using BTF, the type inक्रमmation and values are
 *		stored in the first *str_size* - 1 bytes of *str*.  Safe copy of
 *		the poपूर्णांकer data is carried out to aव्योम kernel crashes during
 *		operation.  Smaller types can use string space on the stack;
 *		larger programs can use map data to store the string
 *		representation.
 *
 *		The string can be subsequently shared with userspace via
 *		bpf_perf_event_output() or ring buffer पूर्णांकerfaces.
 *		bpf_trace_prपूर्णांकk() is to be aव्योमed as it places too small
 *		a limit on string size to be useful.
 *
 *		*flags* is a combination of
 *
 *		**BTF_F_COMPACT**
 *			no क्रमmatting around type inक्रमmation
 *		**BTF_F_NONAME**
 *			no काष्ठा/जोड़ member names/types
 *		**BTF_F_PTR_RAW**
 *			show raw (unobfuscated) poपूर्णांकer values;
 *			equivalent to prपूर्णांकk specअगरier %px.
 *		**BTF_F_ZERO**
 *			show zero-valued काष्ठा/जोड़ members; they
 *			are not displayed by शेष
 *
 *	Return
 *		The number of bytes that were written (or would have been
 *		written अगर output had to be truncated due to string size),
 *		or a negative error in हालs of failure.
 *
 * दीर्घ bpf_seq_म_लिखो_btf(काष्ठा seq_file *m, काष्ठा btf_ptr *ptr, u32 ptr_size, u64 flags)
 *	Description
 *		Use BTF to ग_लिखो to seq_ग_लिखो a string representation of
 *		*ptr*->ptr, using *ptr*->type_id as per bpf_snम_लिखो_btf().
 *		*flags* are identical to those used क्रम bpf_snम_लिखो_btf.
 *	Return
 *		0 on success or a negative error in हाल of failure.
 *
 * u64 bpf_skb_cgroup_classid(काष्ठा sk_buff *skb)
 * 	Description
 * 		See **bpf_get_cgroup_classid**\ () क्रम the मुख्य description.
 * 		This helper dअगरfers from **bpf_get_cgroup_classid**\ () in that
 * 		the cgroup v1 net_cls class is retrieved only from the *skb*'s
 * 		associated socket instead of the current process.
 * 	Return
 * 		The id is वापसed or 0 in हाल the id could not be retrieved.
 *
 * दीर्घ bpf_redirect_neigh(u32 अगरindex, काष्ठा bpf_redir_neigh *params, पूर्णांक plen, u64 flags)
 * 	Description
 * 		Redirect the packet to another net device of index *अगरindex*
 * 		and fill in L2 addresses from neighboring subप्रणाली. This helper
 * 		is somewhat similar to **bpf_redirect**\ (), except that it
 * 		populates L2 addresses as well, meaning, पूर्णांकernally, the helper
 * 		relies on the neighbor lookup क्रम the L2 address of the nexthop.
 *
 * 		The helper will perक्रमm a FIB lookup based on the skb's
 * 		networking header to get the address of the next hop, unless
 * 		this is supplied by the caller in the *params* argument. The
 * 		*plen* argument indicates the len of *params* and should be set
 * 		to 0 अगर *params* is शून्य.
 *
 * 		The *flags* argument is reserved and must be 0. The helper is
 * 		currently only supported क्रम tc BPF program types, and enabled
 * 		क्रम IPv4 and IPv6 protocols.
 * 	Return
 * 		The helper वापसs **TC_ACT_REसूचीECT** on success or
 * 		**TC_ACT_SHOT** on error.
 *
 * व्योम *bpf_per_cpu_ptr(स्थिर व्योम *percpu_ptr, u32 cpu)
 *     Description
 *             Take a poपूर्णांकer to a percpu ksym, *percpu_ptr*, and वापस a
 *             poपूर्णांकer to the percpu kernel variable on *cpu*. A ksym is an
 *             बाह्य variable decorated with '__ksym'. For ksym, there is a
 *             global var (either अटल or global) defined of the same name
 *             in the kernel. The ksym is percpu अगर the global var is percpu.
 *             The वापसed poपूर्णांकer poपूर्णांकs to the global percpu var on *cpu*.
 *
 *             bpf_per_cpu_ptr() has the same semantic as per_cpu_ptr() in the
 *             kernel, except that bpf_per_cpu_ptr() may वापस शून्य. This
 *             happens अगर *cpu* is larger than nr_cpu_ids. The caller of
 *             bpf_per_cpu_ptr() must check the वापसed value.
 *     Return
 *             A poपूर्णांकer poपूर्णांकing to the kernel percpu variable on *cpu*, or
 *             शून्य, अगर *cpu* is invalid.
 *
 * व्योम *bpf_this_cpu_ptr(स्थिर व्योम *percpu_ptr)
 *	Description
 *		Take a poपूर्णांकer to a percpu ksym, *percpu_ptr*, and वापस a
 *		poपूर्णांकer to the percpu kernel variable on this cpu. See the
 *		description of 'ksym' in **bpf_per_cpu_ptr**\ ().
 *
 *		bpf_this_cpu_ptr() has the same semantic as this_cpu_ptr() in
 *		the kernel. Dअगरferent from **bpf_per_cpu_ptr**\ (), it would
 *		never वापस शून्य.
 *	Return
 *		A poपूर्णांकer poपूर्णांकing to the kernel percpu variable on this cpu.
 *
 * दीर्घ bpf_redirect_peer(u32 अगरindex, u64 flags)
 * 	Description
 * 		Redirect the packet to another net device of index *अगरindex*.
 * 		This helper is somewhat similar to **bpf_redirect**\ (), except
 * 		that the redirection happens to the *अगरindex*' peer device and
 * 		the netns चयन takes place from ingress to ingress without
 * 		going through the CPU's backlog queue.
 *
 * 		The *flags* argument is reserved and must be 0. The helper is
 * 		currently only supported क्रम tc BPF program types at the ingress
 * 		hook and क्रम veth device types. The peer device must reside in a
 * 		dअगरferent network namespace.
 * 	Return
 * 		The helper वापसs **TC_ACT_REसूचीECT** on success or
 * 		**TC_ACT_SHOT** on error.
 *
 * व्योम *bpf_task_storage_get(काष्ठा bpf_map *map, काष्ठा task_काष्ठा *task, व्योम *value, u64 flags)
 *	Description
 *		Get a bpf_local_storage from the *task*.
 *
 *		Logically, it could be thought of as getting the value from
 *		a *map* with *task* as the **key**.  From this
 *		perspective,  the usage is not much dअगरferent from
 *		**bpf_map_lookup_elem**\ (*map*, **&**\ *task*) except this
 *		helper enक्रमces the key must be an task_काष्ठा and the map must also
 *		be a **BPF_MAP_TYPE_TASK_STORAGE**.
 *
 *		Underneath, the value is stored locally at *task* instead of
 *		the *map*.  The *map* is used as the bpf-local-storage
 *		"type". The bpf-local-storage "type" (i.e. the *map*) is
 *		searched against all bpf_local_storage residing at *task*.
 *
 *		An optional *flags* (**BPF_LOCAL_STORAGE_GET_F_CREATE**) can be
 *		used such that a new bpf_local_storage will be
 *		created अगर one करोes not exist.  *value* can be used
 *		together with **BPF_LOCAL_STORAGE_GET_F_CREATE** to specअगरy
 *		the initial value of a bpf_local_storage.  If *value* is
 *		**शून्य**, the new bpf_local_storage will be zero initialized.
 *	Return
 *		A bpf_local_storage poपूर्णांकer is वापसed on success.
 *
 *		**शून्य** अगर not found or there was an error in adding
 *		a new bpf_local_storage.
 *
 * दीर्घ bpf_task_storage_delete(काष्ठा bpf_map *map, काष्ठा task_काष्ठा *task)
 *	Description
 *		Delete a bpf_local_storage from a *task*.
 *	Return
 *		0 on success.
 *
 *		**-ENOENT** अगर the bpf_local_storage cannot be found.
 *
 * काष्ठा task_काष्ठा *bpf_get_current_task_btf(व्योम)
 *	Description
 *		Return a BTF poपूर्णांकer to the "current" task.
 *		This poपूर्णांकer can also be used in helpers that accept an
 *		*ARG_PTR_TO_BTF_ID* of type *task_काष्ठा*.
 *	Return
 *		Poपूर्णांकer to the current task.
 *
 * दीर्घ bpf_bprm_opts_set(काष्ठा linux_binprm *bprm, u64 flags)
 *	Description
 *		Set or clear certain options on *bprm*:
 *
 *		**BPF_F_BPRM_SECUREEXEC** Set the secureexec bit
 *		which sets the **AT_SECURE** auxv क्रम glibc. The bit
 *		is cleared अगर the flag is not specअगरied.
 *	Return
 *		**-EINVAL** अगर invalid *flags* are passed, zero otherwise.
 *
 * u64 bpf_kसमय_get_coarse_ns(व्योम)
 * 	Description
 * 		Return a coarse-grained version of the समय elapsed since
 * 		प्रणाली boot, in nanoseconds. Does not include समय the प्रणाली
 * 		was suspended.
 *
 * 		See: **घड़ी_समय_लो**\ (**CLOCK_MONOTONIC_COARSE**)
 * 	Return
 * 		Current *kसमय*.
 *
 * दीर्घ bpf_ima_inode_hash(काष्ठा inode *inode, व्योम *dst, u32 size)
 *	Description
 *		Returns the stored IMA hash of the *inode* (अगर it's avaialable).
 *		If the hash is larger than *size*, then only *size*
 *		bytes will be copied to *dst*
 *	Return
 *		The **hash_algo** is वापसed on success,
 *		**-EOPNOTSUP** अगर IMA is disabled or **-EINVAL** अगर
 *		invalid arguments are passed.
 *
 * काष्ठा socket *bpf_sock_from_file(काष्ठा file *file)
 *	Description
 *		If the given file represents a socket, वापसs the associated
 *		socket.
 *	Return
 *		A poपूर्णांकer to a काष्ठा socket on success or शून्य अगर the file is
 *		not a socket.
 *
 * दीर्घ bpf_check_mtu(व्योम *ctx, u32 अगरindex, u32 *mtu_len, s32 len_dअगरf, u64 flags)
 *	Description
 *		Check packet size against exceeding MTU of net device (based
 *		on *अगरindex*).  This helper will likely be used in combination
 *		with helpers that adjust/change the packet size.
 *
 *		The argument *len_dअगरf* can be used क्रम querying with a planned
 *		size change. This allows to check MTU prior to changing packet
 *		ctx. Providing an *len_dअगरf* adjusपंचांगent that is larger than the
 *		actual packet size (resulting in negative packet size) will in
 *		principle not exceed the MTU, why it is not considered a
 *		failure.  Other BPF-helpers are needed क्रम perक्रमming the
 *		planned size change, why the responsability क्रम catch a negative
 *		packet size beदीर्घ in those helpers.
 *
 *		Specअगरying *अगरindex* zero means the MTU check is perक्रमmed
 *		against the current net device.  This is practical अगर this isn't
 *		used prior to redirect.
 *
 *		On input *mtu_len* must be a valid poपूर्णांकer, अन्यथा verअगरier will
 *		reject BPF program.  If the value *mtu_len* is initialized to
 *		zero then the ctx packet size is use.  When value *mtu_len* is
 *		provided as input this specअगरy the L3 length that the MTU check
 *		is करोne against. Remember XDP and TC length operate at L2, but
 *		this value is L3 as this correlate to MTU and IP-header tot_len
 *		values which are L3 (similar behavior as bpf_fib_lookup).
 *
 *		The Linux kernel route table can configure MTUs on a more
 *		specअगरic per route level, which is not provided by this helper.
 *		For route level MTU checks use the **bpf_fib_lookup**\ ()
 *		helper.
 *
 *		*ctx* is either **काष्ठा xdp_md** क्रम XDP programs or
 *		**काष्ठा sk_buff** क्रम tc cls_act programs.
 *
 *		The *flags* argument can be a combination of one or more of the
 *		following values:
 *
 *		**BPF_MTU_CHK_SEGS**
 *			This flag will only works क्रम *ctx* **काष्ठा sk_buff**.
 *			If packet context contains extra packet segment buffers
 *			(often knows as GSO skb), then MTU check is harder to
 *			check at this poपूर्णांक, because in transmit path it is
 *			possible क्रम the skb packet to get re-segmented
 *			(depending on net device features).  This could still be
 *			a MTU violation, so this flag enables perक्रमming MTU
 *			check against segments, with a dअगरferent violation
 *			वापस code to tell it apart. Check cannot use len_dअगरf.
 *
 *		On वापस *mtu_len* poपूर्णांकer contains the MTU value of the net
 *		device.  Remember the net device configured MTU is the L3 size,
 *		which is वापसed here and XDP and TC length operate at L2.
 *		Helper take this पूर्णांकo account क्रम you, but remember when using
 *		MTU value in your BPF-code.
 *
 *	Return
 *		* 0 on success, and populate MTU value in *mtu_len* poपूर्णांकer.
 *
 *		* < 0 अगर any input argument is invalid (*mtu_len* not updated)
 *
 *		MTU violations वापस positive values, but also populate MTU
 *		value in *mtu_len* poपूर्णांकer, as this can be needed क्रम
 *		implementing PMTU handing:
 *
 *		* **BPF_MTU_CHK_RET_FRAG_NEEDED**
 *		* **BPF_MTU_CHK_RET_SEGS_TOOBIG**
 *
 * दीर्घ bpf_क्रम_each_map_elem(काष्ठा bpf_map *map, व्योम *callback_fn, व्योम *callback_ctx, u64 flags)
 *	Description
 *		For each element in **map**, call **callback_fn** function with
 *		**map**, **callback_ctx** and other map-specअगरic parameters.
 *		The **callback_fn** should be a अटल function and
 *		the **callback_ctx** should be a poपूर्णांकer to the stack.
 *		The **flags** is used to control certain aspects of the helper.
 *		Currently, the **flags** must be 0.
 *
 *		The following are a list of supported map types and their
 *		respective expected callback signatures:
 *
 *		BPF_MAP_TYPE_HASH, BPF_MAP_TYPE_PERCPU_HASH,
 *		BPF_MAP_TYPE_LRU_HASH, BPF_MAP_TYPE_LRU_PERCPU_HASH,
 *		BPF_MAP_TYPE_ARRAY, BPF_MAP_TYPE_PERCPU_ARRAY
 *
 *		दीर्घ (\*callback_fn)(काष्ठा bpf_map \*map, स्थिर व्योम \*key, व्योम \*value, व्योम \*ctx);
 *
 *		For per_cpu maps, the map_value is the value on the cpu where the
 *		bpf_prog is running.
 *
 *		If **callback_fn** वापस 0, the helper will जारी to the next
 *		element. If वापस value is 1, the helper will skip the rest of
 *		elements and वापस. Other वापस values are not used now.
 *
 *	Return
 *		The number of traversed map elements क्रम success, **-EINVAL** क्रम
 *		invalid **flags**.
 *
 * दीर्घ bpf_snम_लिखो(अक्षर *str, u32 str_size, स्थिर अक्षर *fmt, u64 *data, u32 data_len)
 *	Description
 *		Outमाला_दो a string पूर्णांकo the **str** buffer of size **str_size**
 *		based on a क्रमmat string stored in a पढ़ो-only map poपूर्णांकed by
 *		**fmt**.
 *
 *		Each क्रमmat specअगरier in **fmt** corresponds to one u64 element
 *		in the **data** array. For strings and poपूर्णांकers where poपूर्णांकees
 *		are accessed, only the poपूर्णांकer values are stored in the *data*
 *		array. The *data_len* is the size of *data* in bytes.
 *
 *		Formats **%s** and **%pअणुi,Iपूर्णअणु4,6पूर्ण** require to पढ़ो kernel
 *		memory. Reading kernel memory may fail due to either invalid
 *		address or valid address but requiring a major memory fault. If
 *		पढ़ोing kernel memory fails, the string क्रम **%s** will be an
 *		empty string, and the ip address क्रम **%pअणुi,Iपूर्णअणु4,6पूर्ण** will be 0.
 *		Not वापसing error to bpf program is consistent with what
 *		**bpf_trace_prपूर्णांकk**\ () करोes क्रम now.
 *
 *	Return
 *		The strictly positive length of the क्रमmatted string, including
 *		the trailing zero अक्षरacter. If the वापस value is greater than
 *		**str_size**, **str** contains a truncated string, guaranteed to
 *		be zero-terminated except when **str_size** is 0.
 *
 *		Or **-EBUSY** अगर the per-CPU memory copy buffer is busy.
 */
#घोषणा __BPF_FUNC_MAPPER(FN)		\
	FN(unspec),			\
	FN(map_lookup_elem),		\
	FN(map_update_elem),		\
	FN(map_delete_elem),		\
	FN(probe_पढ़ो),			\
	FN(kसमय_get_ns),		\
	FN(trace_prपूर्णांकk),		\
	FN(get_pअक्रमom_u32),		\
	FN(get_smp_processor_id),	\
	FN(skb_store_bytes),		\
	FN(l3_csum_replace),		\
	FN(l4_csum_replace),		\
	FN(tail_call),			\
	FN(clone_redirect),		\
	FN(get_current_pid_tgid),	\
	FN(get_current_uid_gid),	\
	FN(get_current_comm),		\
	FN(get_cgroup_classid),		\
	FN(skb_vlan_push),		\
	FN(skb_vlan_pop),		\
	FN(skb_get_tunnel_key),		\
	FN(skb_set_tunnel_key),		\
	FN(perf_event_पढ़ो),		\
	FN(redirect),			\
	FN(get_route_realm),		\
	FN(perf_event_output),		\
	FN(skb_load_bytes),		\
	FN(get_stackid),		\
	FN(csum_dअगरf),			\
	FN(skb_get_tunnel_opt),		\
	FN(skb_set_tunnel_opt),		\
	FN(skb_change_proto),		\
	FN(skb_change_type),		\
	FN(skb_under_cgroup),		\
	FN(get_hash_recalc),		\
	FN(get_current_task),		\
	FN(probe_ग_लिखो_user),		\
	FN(current_task_under_cgroup),	\
	FN(skb_change_tail),		\
	FN(skb_pull_data),		\
	FN(csum_update),		\
	FN(set_hash_invalid),		\
	FN(get_numa_node_id),		\
	FN(skb_change_head),		\
	FN(xdp_adjust_head),		\
	FN(probe_पढ़ो_str),		\
	FN(get_socket_cookie),		\
	FN(get_socket_uid),		\
	FN(set_hash),			\
	FN(setsockopt),			\
	FN(skb_adjust_room),		\
	FN(redirect_map),		\
	FN(sk_redirect_map),		\
	FN(sock_map_update),		\
	FN(xdp_adjust_meta),		\
	FN(perf_event_पढ़ो_value),	\
	FN(perf_prog_पढ़ो_value),	\
	FN(माला_लोockopt),			\
	FN(override_वापस),		\
	FN(sock_ops_cb_flags_set),	\
	FN(msg_redirect_map),		\
	FN(msg_apply_bytes),		\
	FN(msg_cork_bytes),		\
	FN(msg_pull_data),		\
	FN(bind),			\
	FN(xdp_adjust_tail),		\
	FN(skb_get_xfrm_state),		\
	FN(get_stack),			\
	FN(skb_load_bytes_relative),	\
	FN(fib_lookup),			\
	FN(sock_hash_update),		\
	FN(msg_redirect_hash),		\
	FN(sk_redirect_hash),		\
	FN(lwt_push_encap),		\
	FN(lwt_seg6_store_bytes),	\
	FN(lwt_seg6_adjust_srh),	\
	FN(lwt_seg6_action),		\
	FN(rc_repeat),			\
	FN(rc_keyकरोwn),			\
	FN(skb_cgroup_id),		\
	FN(get_current_cgroup_id),	\
	FN(get_local_storage),		\
	FN(sk_select_reuseport),	\
	FN(skb_ancestor_cgroup_id),	\
	FN(sk_lookup_tcp),		\
	FN(sk_lookup_udp),		\
	FN(sk_release),			\
	FN(map_push_elem),		\
	FN(map_pop_elem),		\
	FN(map_peek_elem),		\
	FN(msg_push_data),		\
	FN(msg_pop_data),		\
	FN(rc_poपूर्णांकer_rel),		\
	FN(spin_lock),			\
	FN(spin_unlock),		\
	FN(sk_fullsock),		\
	FN(tcp_sock),			\
	FN(skb_ecn_set_ce),		\
	FN(get_listener_sock),		\
	FN(skc_lookup_tcp),		\
	FN(tcp_check_syncookie),	\
	FN(sysctl_get_name),		\
	FN(sysctl_get_current_value),	\
	FN(sysctl_get_new_value),	\
	FN(sysctl_set_new_value),	\
	FN(म_से_दीर्घ),			\
	FN(म_से_अदीर्घ),			\
	FN(sk_storage_get),		\
	FN(sk_storage_delete),		\
	FN(send_संकेत),		\
	FN(tcp_gen_syncookie),		\
	FN(skb_output),			\
	FN(probe_पढ़ो_user),		\
	FN(probe_पढ़ो_kernel),		\
	FN(probe_पढ़ो_user_str),	\
	FN(probe_पढ़ो_kernel_str),	\
	FN(tcp_send_ack),		\
	FN(send_संकेत_thपढ़ो),		\
	FN(jअगरfies64),			\
	FN(पढ़ो_branch_records),	\
	FN(get_ns_current_pid_tgid),	\
	FN(xdp_output),			\
	FN(get_netns_cookie),		\
	FN(get_current_ancestor_cgroup_id),	\
	FN(sk_assign),			\
	FN(kसमय_get_boot_ns),		\
	FN(seq_म_लिखो),			\
	FN(seq_ग_लिखो),			\
	FN(sk_cgroup_id),		\
	FN(sk_ancestor_cgroup_id),	\
	FN(ringbuf_output),		\
	FN(ringbuf_reserve),		\
	FN(ringbuf_submit),		\
	FN(ringbuf_discard),		\
	FN(ringbuf_query),		\
	FN(csum_level),			\
	FN(skc_to_tcp6_sock),		\
	FN(skc_to_tcp_sock),		\
	FN(skc_to_tcp_समयरुको_sock),	\
	FN(skc_to_tcp_request_sock),	\
	FN(skc_to_udp6_sock),		\
	FN(get_task_stack),		\
	FN(load_hdr_opt),		\
	FN(store_hdr_opt),		\
	FN(reserve_hdr_opt),		\
	FN(inode_storage_get),		\
	FN(inode_storage_delete),	\
	FN(d_path),			\
	FN(copy_from_user),		\
	FN(snम_लिखो_btf),		\
	FN(seq_म_लिखो_btf),		\
	FN(skb_cgroup_classid),		\
	FN(redirect_neigh),		\
	FN(per_cpu_ptr),		\
	FN(this_cpu_ptr),		\
	FN(redirect_peer),		\
	FN(task_storage_get),		\
	FN(task_storage_delete),	\
	FN(get_current_task_btf),	\
	FN(bprm_opts_set),		\
	FN(kसमय_get_coarse_ns),	\
	FN(ima_inode_hash),		\
	FN(sock_from_file),		\
	FN(check_mtu),			\
	FN(क्रम_each_map_elem),		\
	FN(snम_लिखो),			\
	/* */

/* पूर्णांकeger value in 'imm' field of BPF_CALL inकाष्ठाion selects which helper
 * function eBPF program पूर्णांकends to call
 */
#घोषणा __BPF_ENUM_FN(x) BPF_FUNC_ ## x
क्रमागत bpf_func_id अणु
	__BPF_FUNC_MAPPER(__BPF_ENUM_FN)
	__BPF_FUNC_MAX_ID,
पूर्ण;
#अघोषित __BPF_ENUM_FN

/* All flags used by eBPF helper functions, placed here. */

/* BPF_FUNC_skb_store_bytes flags. */
क्रमागत अणु
	BPF_F_RECOMPUTE_CSUM		= (1ULL << 0),
	BPF_F_INVALIDATE_HASH		= (1ULL << 1),
पूर्ण;

/* BPF_FUNC_l3_csum_replace and BPF_FUNC_l4_csum_replace flags.
 * First 4 bits are क्रम passing the header field size.
 */
क्रमागत अणु
	BPF_F_HDR_FIELD_MASK		= 0xfULL,
पूर्ण;

/* BPF_FUNC_l4_csum_replace flags. */
क्रमागत अणु
	BPF_F_PSEUDO_HDR		= (1ULL << 4),
	BPF_F_MARK_MANGLED_0		= (1ULL << 5),
	BPF_F_MARK_ENFORCE		= (1ULL << 6),
पूर्ण;

/* BPF_FUNC_clone_redirect and BPF_FUNC_redirect flags. */
क्रमागत अणु
	BPF_F_INGRESS			= (1ULL << 0),
पूर्ण;

/* BPF_FUNC_skb_set_tunnel_key and BPF_FUNC_skb_get_tunnel_key flags. */
क्रमागत अणु
	BPF_F_TUNINFO_IPV6		= (1ULL << 0),
पूर्ण;

/* flags क्रम both BPF_FUNC_get_stackid and BPF_FUNC_get_stack. */
क्रमागत अणु
	BPF_F_SKIP_FIELD_MASK		= 0xffULL,
	BPF_F_USER_STACK		= (1ULL << 8),
/* flags used by BPF_FUNC_get_stackid only. */
	BPF_F_FAST_STACK_CMP		= (1ULL << 9),
	BPF_F_REUSE_STACKID		= (1ULL << 10),
/* flags used by BPF_FUNC_get_stack only. */
	BPF_F_USER_BUILD_ID		= (1ULL << 11),
पूर्ण;

/* BPF_FUNC_skb_set_tunnel_key flags. */
क्रमागत अणु
	BPF_F_ZERO_CSUM_TX		= (1ULL << 1),
	BPF_F_DONT_FRAGMENT		= (1ULL << 2),
	BPF_F_SEQ_NUMBER		= (1ULL << 3),
पूर्ण;

/* BPF_FUNC_perf_event_output, BPF_FUNC_perf_event_पढ़ो and
 * BPF_FUNC_perf_event_पढ़ो_value flags.
 */
क्रमागत अणु
	BPF_F_INDEX_MASK		= 0xffffffffULL,
	BPF_F_CURRENT_CPU		= BPF_F_INDEX_MASK,
/* BPF_FUNC_perf_event_output क्रम sk_buff input context. */
	BPF_F_CTXLEN_MASK		= (0xfffffULL << 32),
पूर्ण;

/* Current network namespace */
क्रमागत अणु
	BPF_F_CURRENT_NETNS		= (-1L),
पूर्ण;

/* BPF_FUNC_csum_level level values. */
क्रमागत अणु
	BPF_CSUM_LEVEL_QUERY,
	BPF_CSUM_LEVEL_INC,
	BPF_CSUM_LEVEL_DEC,
	BPF_CSUM_LEVEL_RESET,
पूर्ण;

/* BPF_FUNC_skb_adjust_room flags. */
क्रमागत अणु
	BPF_F_ADJ_ROOM_FIXED_GSO	= (1ULL << 0),
	BPF_F_ADJ_ROOM_ENCAP_L3_IPV4	= (1ULL << 1),
	BPF_F_ADJ_ROOM_ENCAP_L3_IPV6	= (1ULL << 2),
	BPF_F_ADJ_ROOM_ENCAP_L4_GRE	= (1ULL << 3),
	BPF_F_ADJ_ROOM_ENCAP_L4_UDP	= (1ULL << 4),
	BPF_F_ADJ_ROOM_NO_CSUM_RESET	= (1ULL << 5),
	BPF_F_ADJ_ROOM_ENCAP_L2_ETH	= (1ULL << 6),
पूर्ण;

क्रमागत अणु
	BPF_ADJ_ROOM_ENCAP_L2_MASK	= 0xff,
	BPF_ADJ_ROOM_ENCAP_L2_SHIFT	= 56,
पूर्ण;

#घोषणा BPF_F_ADJ_ROOM_ENCAP_L2(len)	(((__u64)len & \
					  BPF_ADJ_ROOM_ENCAP_L2_MASK) \
					 << BPF_ADJ_ROOM_ENCAP_L2_SHIFT)

/* BPF_FUNC_sysctl_get_name flags. */
क्रमागत अणु
	BPF_F_SYSCTL_BASE_NAME		= (1ULL << 0),
पूर्ण;

/* BPF_FUNC_<kernel_obj>_storage_get flags */
क्रमागत अणु
	BPF_LOCAL_STORAGE_GET_F_CREATE	= (1ULL << 0),
	/* BPF_SK_STORAGE_GET_F_CREATE is only kept क्रम backward compatibility
	 * and BPF_LOCAL_STORAGE_GET_F_CREATE must be used instead.
	 */
	BPF_SK_STORAGE_GET_F_CREATE  = BPF_LOCAL_STORAGE_GET_F_CREATE,
पूर्ण;

/* BPF_FUNC_पढ़ो_branch_records flags. */
क्रमागत अणु
	BPF_F_GET_BRANCH_RECORDS_SIZE	= (1ULL << 0),
पूर्ण;

/* BPF_FUNC_bpf_ringbuf_commit, BPF_FUNC_bpf_ringbuf_discard, and
 * BPF_FUNC_bpf_ringbuf_output flags.
 */
क्रमागत अणु
	BPF_RB_NO_WAKEUP		= (1ULL << 0),
	BPF_RB_FORCE_WAKEUP		= (1ULL << 1),
पूर्ण;

/* BPF_FUNC_bpf_ringbuf_query flags */
क्रमागत अणु
	BPF_RB_AVAIL_DATA = 0,
	BPF_RB_RING_SIZE = 1,
	BPF_RB_CONS_POS = 2,
	BPF_RB_PROD_POS = 3,
पूर्ण;

/* BPF ring buffer स्थिरants */
क्रमागत अणु
	BPF_RINGBUF_BUSY_BIT		= (1U << 31),
	BPF_RINGBUF_DISCARD_BIT		= (1U << 30),
	BPF_RINGBUF_HDR_SZ		= 8,
पूर्ण;

/* BPF_FUNC_sk_assign flags in bpf_sk_lookup context. */
क्रमागत अणु
	BPF_SK_LOOKUP_F_REPLACE		= (1ULL << 0),
	BPF_SK_LOOKUP_F_NO_REUSEPORT	= (1ULL << 1),
पूर्ण;

/* Mode क्रम BPF_FUNC_skb_adjust_room helper. */
क्रमागत bpf_adj_room_mode अणु
	BPF_ADJ_ROOM_NET,
	BPF_ADJ_ROOM_MAC,
पूर्ण;

/* Mode क्रम BPF_FUNC_skb_load_bytes_relative helper. */
क्रमागत bpf_hdr_start_off अणु
	BPF_HDR_START_MAC,
	BPF_HDR_START_NET,
पूर्ण;

/* Encapsulation type क्रम BPF_FUNC_lwt_push_encap helper. */
क्रमागत bpf_lwt_encap_mode अणु
	BPF_LWT_ENCAP_SEG6,
	BPF_LWT_ENCAP_SEG6_INLINE,
	BPF_LWT_ENCAP_IP,
पूर्ण;

/* Flags क्रम bpf_bprm_opts_set helper */
क्रमागत अणु
	BPF_F_BPRM_SECUREEXEC	= (1ULL << 0),
पूर्ण;

#घोषणा __bpf_md_ptr(type, name)	\
जोड़ अणु					\
	type name;			\
	__u64 :64;			\
पूर्ण __attribute__((aligned(8)))

/* user accessible mirror of in-kernel sk_buff.
 * new fields can only be added to the end of this काष्ठाure
 */
काष्ठा __sk_buff अणु
	__u32 len;
	__u32 pkt_type;
	__u32 mark;
	__u32 queue_mapping;
	__u32 protocol;
	__u32 vlan_present;
	__u32 vlan_tci;
	__u32 vlan_proto;
	__u32 priority;
	__u32 ingress_अगरindex;
	__u32 अगरindex;
	__u32 tc_index;
	__u32 cb[5];
	__u32 hash;
	__u32 tc_classid;
	__u32 data;
	__u32 data_end;
	__u32 napi_id;

	/* Accessed by BPF_PROG_TYPE_sk_skb types from here to ... */
	__u32 family;
	__u32 remote_ip4;	/* Stored in network byte order */
	__u32 local_ip4;	/* Stored in network byte order */
	__u32 remote_ip6[4];	/* Stored in network byte order */
	__u32 local_ip6[4];	/* Stored in network byte order */
	__u32 remote_port;	/* Stored in network byte order */
	__u32 local_port;	/* stored in host byte order */
	/* ... here. */

	__u32 data_meta;
	__bpf_md_ptr(काष्ठा bpf_flow_keys *, flow_keys);
	__u64 tstamp;
	__u32 wire_len;
	__u32 gso_segs;
	__bpf_md_ptr(काष्ठा bpf_sock *, sk);
	__u32 gso_size;
पूर्ण;

काष्ठा bpf_tunnel_key अणु
	__u32 tunnel_id;
	जोड़ अणु
		__u32 remote_ipv4;
		__u32 remote_ipv6[4];
	पूर्ण;
	__u8 tunnel_tos;
	__u8 tunnel_ttl;
	__u16 tunnel_ext;	/* Padding, future use. */
	__u32 tunnel_label;
पूर्ण;

/* user accessible mirror of in-kernel xfrm_state.
 * new fields can only be added to the end of this काष्ठाure
 */
काष्ठा bpf_xfrm_state अणु
	__u32 reqid;
	__u32 spi;	/* Stored in network byte order */
	__u16 family;
	__u16 ext;	/* Padding, future use. */
	जोड़ अणु
		__u32 remote_ipv4;	/* Stored in network byte order */
		__u32 remote_ipv6[4];	/* Stored in network byte order */
	पूर्ण;
पूर्ण;

/* Generic BPF वापस codes which all BPF program types may support.
 * The values are binary compatible with their TC_ACT_* counter-part to
 * provide backwards compatibility with existing SCHED_CLS and SCHED_ACT
 * programs.
 *
 * XDP is handled seprately, see XDP_*.
 */
क्रमागत bpf_ret_code अणु
	BPF_OK = 0,
	/* 1 reserved */
	BPF_DROP = 2,
	/* 3-6 reserved */
	BPF_REसूचीECT = 7,
	/* >127 are reserved क्रम prog type specअगरic वापस codes.
	 *
	 * BPF_LWT_REROUTE: used by BPF_PROG_TYPE_LWT_IN and
	 *    BPF_PROG_TYPE_LWT_XMIT to indicate that skb had been
	 *    changed and should be routed based on its new L3 header.
	 *    (This is an L3 redirect, as opposed to L2 redirect
	 *    represented by BPF_REसूचीECT above).
	 */
	BPF_LWT_REROUTE = 128,
पूर्ण;

काष्ठा bpf_sock अणु
	__u32 bound_dev_अगर;
	__u32 family;
	__u32 type;
	__u32 protocol;
	__u32 mark;
	__u32 priority;
	/* IP address also allows 1 and 2 bytes access */
	__u32 src_ip4;
	__u32 src_ip6[4];
	__u32 src_port;		/* host byte order */
	__u32 dst_port;		/* network byte order */
	__u32 dst_ip4;
	__u32 dst_ip6[4];
	__u32 state;
	__s32 rx_queue_mapping;
पूर्ण;

काष्ठा bpf_tcp_sock अणु
	__u32 snd_cwnd;		/* Sending congestion winकरोw		*/
	__u32 srtt_us;		/* smoothed round trip समय << 3 in usecs */
	__u32 rtt_min;
	__u32 snd_ssthresh;	/* Slow start size threshold		*/
	__u32 rcv_nxt;		/* What we want to receive next		*/
	__u32 snd_nxt;		/* Next sequence we send		*/
	__u32 snd_una;		/* First byte we want an ack क्रम	*/
	__u32 mss_cache;	/* Cached effective mss, not including SACKS */
	__u32 ecn_flags;	/* ECN status bits.			*/
	__u32 rate_delivered;	/* saved rate sample: packets delivered */
	__u32 rate_पूर्णांकerval_us;	/* saved rate sample: समय elapsed */
	__u32 packets_out;	/* Packets which are "in flight"	*/
	__u32 retrans_out;	/* Retransmitted packets out		*/
	__u32 total_retrans;	/* Total retransmits क्रम entire connection */
	__u32 segs_in;		/* RFC4898 tcpEStatsPerfSegsIn
				 * total number of segments in.
				 */
	__u32 data_segs_in;	/* RFC4898 tcpEStatsPerfDataSegsIn
				 * total number of data segments in.
				 */
	__u32 segs_out;		/* RFC4898 tcpEStatsPerfSegsOut
				 * The total number of segments sent.
				 */
	__u32 data_segs_out;	/* RFC4898 tcpEStatsPerfDataSegsOut
				 * total number of data segments sent.
				 */
	__u32 lost_out;		/* Lost packets			*/
	__u32 sacked_out;	/* SACK'd packets			*/
	__u64 bytes_received;	/* RFC4898 tcpEStatsAppHCThruOctetsReceived
				 * sum(delta(rcv_nxt)), or how many bytes
				 * were acked.
				 */
	__u64 bytes_acked;	/* RFC4898 tcpEStatsAppHCThruOctetsAcked
				 * sum(delta(snd_una)), or how many bytes
				 * were acked.
				 */
	__u32 dsack_dups;	/* RFC4898 tcpEStatsStackDSACKDups
				 * total number of DSACK blocks received
				 */
	__u32 delivered;	/* Total data packets delivered incl. rexmits */
	__u32 delivered_ce;	/* Like the above but only ECE marked packets */
	__u32 icsk_retransmits;	/* Number of unrecovered [RTO] समयouts */
पूर्ण;

काष्ठा bpf_sock_tuple अणु
	जोड़ अणु
		काष्ठा अणु
			__be32 saddr;
			__be32 daddr;
			__be16 sport;
			__be16 dport;
		पूर्ण ipv4;
		काष्ठा अणु
			__be32 saddr[4];
			__be32 daddr[4];
			__be16 sport;
			__be16 dport;
		पूर्ण ipv6;
	पूर्ण;
पूर्ण;

काष्ठा bpf_xdp_sock अणु
	__u32 queue_id;
पूर्ण;

#घोषणा XDP_PACKET_HEADROOM 256

/* User वापस codes क्रम XDP prog type.
 * A valid XDP program must वापस one of these defined values. All other
 * वापस codes are reserved क्रम future use. Unknown वापस codes will
 * result in packet drops and a warning via bpf_warn_invalid_xdp_action().
 */
क्रमागत xdp_action अणु
	XDP_ABORTED = 0,
	XDP_DROP,
	XDP_PASS,
	XDP_TX,
	XDP_REसूचीECT,
पूर्ण;

/* user accessible metadata क्रम XDP packet hook
 * new fields must be added to the end of this काष्ठाure
 */
काष्ठा xdp_md अणु
	__u32 data;
	__u32 data_end;
	__u32 data_meta;
	/* Below access go through काष्ठा xdp_rxq_info */
	__u32 ingress_अगरindex; /* rxq->dev->अगरindex */
	__u32 rx_queue_index;  /* rxq->queue_index  */

	__u32 egress_अगरindex;  /* txq->dev->अगरindex */
पूर्ण;

/* DEVMAP map-value layout
 *
 * The काष्ठा data-layout of map-value is a configuration पूर्णांकerface.
 * New members can only be added to the end of this काष्ठाure.
 */
काष्ठा bpf_devmap_val अणु
	__u32 अगरindex;   /* device index */
	जोड़ अणु
		पूर्णांक   fd;  /* prog fd on map ग_लिखो */
		__u32 id;  /* prog id on map पढ़ो */
	पूर्ण bpf_prog;
पूर्ण;

/* CPUMAP map-value layout
 *
 * The काष्ठा data-layout of map-value is a configuration पूर्णांकerface.
 * New members can only be added to the end of this काष्ठाure.
 */
काष्ठा bpf_cpumap_val अणु
	__u32 qsize;	/* queue size to remote target CPU */
	जोड़ अणु
		पूर्णांक   fd;	/* prog fd on map ग_लिखो */
		__u32 id;	/* prog id on map पढ़ो */
	पूर्ण bpf_prog;
पूर्ण;

क्रमागत sk_action अणु
	SK_DROP = 0,
	SK_PASS,
पूर्ण;

/* user accessible metadata क्रम SK_MSG packet hook, new fields must
 * be added to the end of this काष्ठाure
 */
काष्ठा sk_msg_md अणु
	__bpf_md_ptr(व्योम *, data);
	__bpf_md_ptr(व्योम *, data_end);

	__u32 family;
	__u32 remote_ip4;	/* Stored in network byte order */
	__u32 local_ip4;	/* Stored in network byte order */
	__u32 remote_ip6[4];	/* Stored in network byte order */
	__u32 local_ip6[4];	/* Stored in network byte order */
	__u32 remote_port;	/* Stored in network byte order */
	__u32 local_port;	/* stored in host byte order */
	__u32 size;		/* Total size of sk_msg */

	__bpf_md_ptr(काष्ठा bpf_sock *, sk); /* current socket */
पूर्ण;

काष्ठा sk_reuseport_md अणु
	/*
	 * Start of directly accessible data. It begins from
	 * the tcp/udp header.
	 */
	__bpf_md_ptr(व्योम *, data);
	/* End of directly accessible data */
	__bpf_md_ptr(व्योम *, data_end);
	/*
	 * Total length of packet (starting from the tcp/udp header).
	 * Note that the directly accessible bytes (data_end - data)
	 * could be less than this "len".  Those bytes could be
	 * indirectly पढ़ो by a helper "bpf_skb_load_bytes()".
	 */
	__u32 len;
	/*
	 * Eth protocol in the mac header (network byte order). e.g.
	 * ETH_P_IP(0x0800) and ETH_P_IPV6(0x86DD)
	 */
	__u32 eth_protocol;
	__u32 ip_protocol;	/* IP protocol. e.g. IPPROTO_TCP, IPPROTO_UDP */
	__u32 bind_inany;	/* Is sock bound to an Iन_अंकY address? */
	__u32 hash;		/* A hash of the packet 4 tuples */
पूर्ण;

#घोषणा BPF_TAG_SIZE	8

काष्ठा bpf_prog_info अणु
	__u32 type;
	__u32 id;
	__u8  tag[BPF_TAG_SIZE];
	__u32 jited_prog_len;
	__u32 xlated_prog_len;
	__aligned_u64 jited_prog_insns;
	__aligned_u64 xlated_prog_insns;
	__u64 load_समय;	/* ns since bootसमय */
	__u32 created_by_uid;
	__u32 nr_map_ids;
	__aligned_u64 map_ids;
	अक्षर name[BPF_OBJ_NAME_LEN];
	__u32 अगरindex;
	__u32 gpl_compatible:1;
	__u32 :31; /* alignment pad */
	__u64 netns_dev;
	__u64 netns_ino;
	__u32 nr_jited_ksyms;
	__u32 nr_jited_func_lens;
	__aligned_u64 jited_ksyms;
	__aligned_u64 jited_func_lens;
	__u32 btf_id;
	__u32 func_info_rec_size;
	__aligned_u64 func_info;
	__u32 nr_func_info;
	__u32 nr_line_info;
	__aligned_u64 line_info;
	__aligned_u64 jited_line_info;
	__u32 nr_jited_line_info;
	__u32 line_info_rec_size;
	__u32 jited_line_info_rec_size;
	__u32 nr_prog_tags;
	__aligned_u64 prog_tags;
	__u64 run_समय_ns;
	__u64 run_cnt;
	__u64 recursion_misses;
पूर्ण __attribute__((aligned(8)));

काष्ठा bpf_map_info अणु
	__u32 type;
	__u32 id;
	__u32 key_size;
	__u32 value_size;
	__u32 max_entries;
	__u32 map_flags;
	अक्षर  name[BPF_OBJ_NAME_LEN];
	__u32 अगरindex;
	__u32 btf_vmlinux_value_type_id;
	__u64 netns_dev;
	__u64 netns_ino;
	__u32 btf_id;
	__u32 btf_key_type_id;
	__u32 btf_value_type_id;
पूर्ण __attribute__((aligned(8)));

काष्ठा bpf_btf_info अणु
	__aligned_u64 btf;
	__u32 btf_size;
	__u32 id;
	__aligned_u64 name;
	__u32 name_len;
	__u32 kernel_btf;
पूर्ण __attribute__((aligned(8)));

काष्ठा bpf_link_info अणु
	__u32 type;
	__u32 id;
	__u32 prog_id;
	जोड़ अणु
		काष्ठा अणु
			__aligned_u64 tp_name; /* in/out: tp_name buffer ptr */
			__u32 tp_name_len;     /* in/out: tp_name buffer len */
		पूर्ण raw_tracepoपूर्णांक;
		काष्ठा अणु
			__u32 attach_type;
			__u32 target_obj_id; /* prog_id क्रम PROG_EXT, otherwise btf object id */
			__u32 target_btf_id; /* BTF type id inside the object */
		पूर्ण tracing;
		काष्ठा अणु
			__u64 cgroup_id;
			__u32 attach_type;
		पूर्ण cgroup;
		काष्ठा अणु
			__aligned_u64 target_name; /* in/out: target_name buffer ptr */
			__u32 target_name_len;	   /* in/out: target_name buffer len */
			जोड़ अणु
				काष्ठा अणु
					__u32 map_id;
				पूर्ण map;
			पूर्ण;
		पूर्ण iter;
		काष्ठा  अणु
			__u32 netns_ino;
			__u32 attach_type;
		पूर्ण netns;
		काष्ठा अणु
			__u32 अगरindex;
		पूर्ण xdp;
	पूर्ण;
पूर्ण __attribute__((aligned(8)));

/* User bpf_sock_addr काष्ठा to access socket fields and sockaddr काष्ठा passed
 * by user and पूर्णांकended to be used by socket (e.g. to bind to, depends on
 * attach type).
 */
काष्ठा bpf_sock_addr अणु
	__u32 user_family;	/* Allows 4-byte पढ़ो, but no ग_लिखो. */
	__u32 user_ip4;		/* Allows 1,2,4-byte पढ़ो and 4-byte ग_लिखो.
				 * Stored in network byte order.
				 */
	__u32 user_ip6[4];	/* Allows 1,2,4,8-byte पढ़ो and 4,8-byte ग_लिखो.
				 * Stored in network byte order.
				 */
	__u32 user_port;	/* Allows 1,2,4-byte पढ़ो and 4-byte ग_लिखो.
				 * Stored in network byte order
				 */
	__u32 family;		/* Allows 4-byte पढ़ो, but no ग_लिखो */
	__u32 type;		/* Allows 4-byte पढ़ो, but no ग_लिखो */
	__u32 protocol;		/* Allows 4-byte पढ़ो, but no ग_लिखो */
	__u32 msg_src_ip4;	/* Allows 1,2,4-byte पढ़ो and 4-byte ग_लिखो.
				 * Stored in network byte order.
				 */
	__u32 msg_src_ip6[4];	/* Allows 1,2,4,8-byte पढ़ो and 4,8-byte ग_लिखो.
				 * Stored in network byte order.
				 */
	__bpf_md_ptr(काष्ठा bpf_sock *, sk);
पूर्ण;

/* User bpf_sock_ops काष्ठा to access socket values and specअगरy request ops
 * and their replies.
 * Some of this fields are in network (bigendian) byte order and may need
 * to be converted beक्रमe use (bpf_ntohl() defined in samples/bpf/bpf_endian.h).
 * New fields can only be added at the end of this काष्ठाure
 */
काष्ठा bpf_sock_ops अणु
	__u32 op;
	जोड़ अणु
		__u32 args[4];		/* Optionally passed to bpf program */
		__u32 reply;		/* Returned by bpf program	    */
		__u32 replyदीर्घ[4];	/* Optionally वापसed by bpf prog  */
	पूर्ण;
	__u32 family;
	__u32 remote_ip4;	/* Stored in network byte order */
	__u32 local_ip4;	/* Stored in network byte order */
	__u32 remote_ip6[4];	/* Stored in network byte order */
	__u32 local_ip6[4];	/* Stored in network byte order */
	__u32 remote_port;	/* Stored in network byte order */
	__u32 local_port;	/* stored in host byte order */
	__u32 is_fullsock;	/* Some TCP fields are only valid अगर
				 * there is a full socket. If not, the
				 * fields पढ़ो as zero.
				 */
	__u32 snd_cwnd;
	__u32 srtt_us;		/* Averaged RTT << 3 in usecs */
	__u32 bpf_sock_ops_cb_flags; /* flags defined in uapi/linux/tcp.h */
	__u32 state;
	__u32 rtt_min;
	__u32 snd_ssthresh;
	__u32 rcv_nxt;
	__u32 snd_nxt;
	__u32 snd_una;
	__u32 mss_cache;
	__u32 ecn_flags;
	__u32 rate_delivered;
	__u32 rate_पूर्णांकerval_us;
	__u32 packets_out;
	__u32 retrans_out;
	__u32 total_retrans;
	__u32 segs_in;
	__u32 data_segs_in;
	__u32 segs_out;
	__u32 data_segs_out;
	__u32 lost_out;
	__u32 sacked_out;
	__u32 sk_txhash;
	__u64 bytes_received;
	__u64 bytes_acked;
	__bpf_md_ptr(काष्ठा bpf_sock *, sk);
	/* [skb_data, skb_data_end) covers the whole TCP header.
	 *
	 * BPF_SOCK_OPS_PARSE_HDR_OPT_CB: The packet received
	 * BPF_SOCK_OPS_HDR_OPT_LEN_CB:   Not useful because the
	 *                                header has not been written.
	 * BPF_SOCK_OPS_WRITE_HDR_OPT_CB: The header and options have
	 *				  been written so far.
	 * BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB:  The SYNACK that concludes
	 *					the 3WHS.
	 * BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB: The ACK that concludes
	 *					the 3WHS.
	 *
	 * bpf_load_hdr_opt() can also be used to पढ़ो a particular option.
	 */
	__bpf_md_ptr(व्योम *, skb_data);
	__bpf_md_ptr(व्योम *, skb_data_end);
	__u32 skb_len;		/* The total length of a packet.
				 * It includes the header, options,
				 * and payload.
				 */
	__u32 skb_tcp_flags;	/* tcp_flags of the header.  It provides
				 * an easy way to check क्रम tcp_flags
				 * without parsing skb_data.
				 *
				 * In particular, the skb_tcp_flags
				 * will still be available in
				 * BPF_SOCK_OPS_HDR_OPT_LEN even though
				 * the outgoing header has not
				 * been written yet.
				 */
पूर्ण;

/* Definitions क्रम bpf_sock_ops_cb_flags */
क्रमागत अणु
	BPF_SOCK_OPS_RTO_CB_FLAG	= (1<<0),
	BPF_SOCK_OPS_RETRANS_CB_FLAG	= (1<<1),
	BPF_SOCK_OPS_STATE_CB_FLAG	= (1<<2),
	BPF_SOCK_OPS_RTT_CB_FLAG	= (1<<3),
	/* Call bpf क्रम all received TCP headers.  The bpf prog will be
	 * called under sock_ops->op == BPF_SOCK_OPS_PARSE_HDR_OPT_CB
	 *
	 * Please refer to the comment in BPF_SOCK_OPS_PARSE_HDR_OPT_CB
	 * क्रम the header option related helpers that will be useful
	 * to the bpf programs.
	 *
	 * It could be used at the client/active side (i.e. connect() side)
	 * when the server told it that the server was in syncookie
	 * mode and required the active side to resend the bpf-written
	 * options.  The active side can keep writing the bpf-options until
	 * it received a valid packet from the server side to confirm
	 * the earlier packet (and options) has been received.  The later
	 * example patch is using it like this at the active side when the
	 * server is in syncookie mode.
	 *
	 * The bpf prog will usually turn this off in the common हालs.
	 */
	BPF_SOCK_OPS_PARSE_ALL_HDR_OPT_CB_FLAG	= (1<<4),
	/* Call bpf when kernel has received a header option that
	 * the kernel cannot handle.  The bpf prog will be called under
	 * sock_ops->op == BPF_SOCK_OPS_PARSE_HDR_OPT_CB.
	 *
	 * Please refer to the comment in BPF_SOCK_OPS_PARSE_HDR_OPT_CB
	 * क्रम the header option related helpers that will be useful
	 * to the bpf programs.
	 */
	BPF_SOCK_OPS_PARSE_UNKNOWN_HDR_OPT_CB_FLAG = (1<<5),
	/* Call bpf when the kernel is writing header options क्रम the
	 * outgoing packet.  The bpf prog will first be called
	 * to reserve space in a skb under
	 * sock_ops->op == BPF_SOCK_OPS_HDR_OPT_LEN_CB.  Then
	 * the bpf prog will be called to ग_लिखो the header option(s)
	 * under sock_ops->op == BPF_SOCK_OPS_WRITE_HDR_OPT_CB.
	 *
	 * Please refer to the comment in BPF_SOCK_OPS_HDR_OPT_LEN_CB
	 * and BPF_SOCK_OPS_WRITE_HDR_OPT_CB क्रम the header option
	 * related helpers that will be useful to the bpf programs.
	 *
	 * The kernel माला_लो its chance to reserve space and ग_लिखो
	 * options first beक्रमe the BPF program करोes.
	 */
	BPF_SOCK_OPS_WRITE_HDR_OPT_CB_FLAG = (1<<6),
/* Mask of all currently supported cb flags */
	BPF_SOCK_OPS_ALL_CB_FLAGS       = 0x7F,
पूर्ण;

/* List of known BPF sock_ops चालकs.
 * New entries can only be added at the end
 */
क्रमागत अणु
	BPF_SOCK_OPS_VOID,
	BPF_SOCK_OPS_TIMEOUT_INIT,	/* Should वापस SYN-RTO value to use or
					 * -1 अगर शेष value should be used
					 */
	BPF_SOCK_OPS_RWND_INIT,		/* Should वापस initial advertized
					 * winकरोw (in packets) or -1 अगर शेष
					 * value should be used
					 */
	BPF_SOCK_OPS_TCP_CONNECT_CB,	/* Calls BPF program right beक्रमe an
					 * active connection is initialized
					 */
	BPF_SOCK_OPS_ACTIVE_ESTABLISHED_CB,	/* Calls BPF program when an
						 * active connection is
						 * established
						 */
	BPF_SOCK_OPS_PASSIVE_ESTABLISHED_CB,	/* Calls BPF program when a
						 * passive connection is
						 * established
						 */
	BPF_SOCK_OPS_NEEDS_ECN,		/* If connection's congestion control
					 * needs ECN
					 */
	BPF_SOCK_OPS_BASE_RTT,		/* Get base RTT. The correct value is
					 * based on the path and may be
					 * dependent on the congestion control
					 * algorithm. In general it indicates
					 * a congestion threshold. RTTs above
					 * this indicate congestion
					 */
	BPF_SOCK_OPS_RTO_CB,		/* Called when an RTO has triggered.
					 * Arg1: value of icsk_retransmits
					 * Arg2: value of icsk_rto
					 * Arg3: whether RTO has expired
					 */
	BPF_SOCK_OPS_RETRANS_CB,	/* Called when skb is retransmitted.
					 * Arg1: sequence number of 1st byte
					 * Arg2: # segments
					 * Arg3: वापस value of
					 *       tcp_transmit_skb (0 => success)
					 */
	BPF_SOCK_OPS_STATE_CB,		/* Called when TCP changes state.
					 * Arg1: old_state
					 * Arg2: new_state
					 */
	BPF_SOCK_OPS_TCP_LISTEN_CB,	/* Called on listen(2), right after
					 * socket transition to LISTEN state.
					 */
	BPF_SOCK_OPS_RTT_CB,		/* Called on every RTT.
					 */
	BPF_SOCK_OPS_PARSE_HDR_OPT_CB,	/* Parse the header option.
					 * It will be called to handle
					 * the packets received at
					 * an alपढ़ोy established
					 * connection.
					 *
					 * sock_ops->skb_data:
					 * Referring to the received skb.
					 * It covers the TCP header only.
					 *
					 * bpf_load_hdr_opt() can also
					 * be used to search क्रम a
					 * particular option.
					 */
	BPF_SOCK_OPS_HDR_OPT_LEN_CB,	/* Reserve space क्रम writing the
					 * header option later in
					 * BPF_SOCK_OPS_WRITE_HDR_OPT_CB.
					 * Arg1: bool want_cookie. (in
					 *       writing SYNACK only)
					 *
					 * sock_ops->skb_data:
					 * Not available because no header has
					 * been	written yet.
					 *
					 * sock_ops->skb_tcp_flags:
					 * The tcp_flags of the
					 * outgoing skb. (e.g. SYN, ACK, FIN).
					 *
					 * bpf_reserve_hdr_opt() should
					 * be used to reserve space.
					 */
	BPF_SOCK_OPS_WRITE_HDR_OPT_CB,	/* Write the header options
					 * Arg1: bool want_cookie. (in
					 *       writing SYNACK only)
					 *
					 * sock_ops->skb_data:
					 * Referring to the outgoing skb.
					 * It covers the TCP header
					 * that has alपढ़ोy been written
					 * by the kernel and the
					 * earlier bpf-progs.
					 *
					 * sock_ops->skb_tcp_flags:
					 * The tcp_flags of the outgoing
					 * skb. (e.g. SYN, ACK, FIN).
					 *
					 * bpf_store_hdr_opt() should
					 * be used to ग_लिखो the
					 * option.
					 *
					 * bpf_load_hdr_opt() can also
					 * be used to search क्रम a
					 * particular option that
					 * has alपढ़ोy been written
					 * by the kernel or the
					 * earlier bpf-progs.
					 */
पूर्ण;

/* List of TCP states. There is a build check in net/ipv4/tcp.c to detect
 * changes between the TCP and BPF versions. Ideally this should never happen.
 * If it करोes, we need to add code to convert them beक्रमe calling
 * the BPF sock_ops function.
 */
क्रमागत अणु
	BPF_TCP_ESTABLISHED = 1,
	BPF_TCP_SYN_SENT,
	BPF_TCP_SYN_RECV,
	BPF_TCP_FIN_WAIT1,
	BPF_TCP_FIN_WAIT2,
	BPF_TCP_TIME_WAIT,
	BPF_TCP_CLOSE,
	BPF_TCP_CLOSE_WAIT,
	BPF_TCP_LAST_ACK,
	BPF_TCP_LISTEN,
	BPF_TCP_CLOSING,	/* Now a valid state */
	BPF_TCP_NEW_SYN_RECV,

	BPF_TCP_MAX_STATES	/* Leave at the end! */
पूर्ण;

क्रमागत अणु
	TCP_BPF_IW		= 1001,	/* Set TCP initial congestion winकरोw */
	TCP_BPF_SNDCWND_CLAMP	= 1002,	/* Set sndcwnd_clamp */
	TCP_BPF_DELACK_MAX	= 1003, /* Max delay ack in usecs */
	TCP_BPF_RTO_MIN		= 1004, /* Min delay ack in usecs */
	/* Copy the SYN pkt to optval
	 *
	 * BPF_PROG_TYPE_SOCK_OPS only.  It is similar to the
	 * bpf_माला_लोockopt(TCP_SAVED_SYN) but it करोes not limit
	 * to only getting from the saved_syn.  It can either get the
	 * syn packet from:
	 *
	 * 1. the just-received SYN packet (only available when writing the
	 *    SYNACK).  It will be useful when it is not necessary to
	 *    save the SYN packet क्रम latter use.  It is also the only way
	 *    to get the SYN during syncookie mode because the syn
	 *    packet cannot be saved during syncookie.
	 *
	 * OR
	 *
	 * 2. the earlier saved syn which was करोne by
	 *    bpf_setsockopt(TCP_SAVE_SYN).
	 *
	 * The bpf_माला_लोockopt(TCP_BPF_SYN*) option will hide where the
	 * SYN packet is obtained.
	 *
	 * If the bpf-prog करोes not need the IP[46] header,  the
	 * bpf-prog can aव्योम parsing the IP header by using
	 * TCP_BPF_SYN.  Otherwise, the bpf-prog can get both
	 * IP[46] and TCP header by using TCP_BPF_SYN_IP.
	 *
	 *      >0: Total number of bytes copied
	 * -ENOSPC: Not enough space in optval. Only optlen number of
	 *          bytes is copied.
	 * -ENOENT: The SYN skb is not available now and the earlier SYN pkt
	 *	    is not saved by setsockopt(TCP_SAVE_SYN).
	 */
	TCP_BPF_SYN		= 1005, /* Copy the TCP header */
	TCP_BPF_SYN_IP		= 1006, /* Copy the IP[46] and TCP header */
	TCP_BPF_SYN_MAC         = 1007, /* Copy the MAC, IP[46], and TCP header */
पूर्ण;

क्रमागत अणु
	BPF_LOAD_HDR_OPT_TCP_SYN = (1ULL << 0),
पूर्ण;

/* args[0] value during BPF_SOCK_OPS_HDR_OPT_LEN_CB and
 * BPF_SOCK_OPS_WRITE_HDR_OPT_CB.
 */
क्रमागत अणु
	BPF_WRITE_HDR_TCP_CURRENT_MSS = 1,	/* Kernel is finding the
						 * total option spaces
						 * required क्रम an established
						 * sk in order to calculate the
						 * MSS.  No skb is actually
						 * sent.
						 */
	BPF_WRITE_HDR_TCP_SYNACK_COOKIE = 2,	/* Kernel is in syncookie mode
						 * when sending a SYN.
						 */
पूर्ण;

काष्ठा bpf_perf_event_value अणु
	__u64 counter;
	__u64 enabled;
	__u64 running;
पूर्ण;

क्रमागत अणु
	BPF_DEVCG_ACC_MKNOD	= (1ULL << 0),
	BPF_DEVCG_ACC_READ	= (1ULL << 1),
	BPF_DEVCG_ACC_WRITE	= (1ULL << 2),
पूर्ण;

क्रमागत अणु
	BPF_DEVCG_DEV_BLOCK	= (1ULL << 0),
	BPF_DEVCG_DEV_CHAR	= (1ULL << 1),
पूर्ण;

काष्ठा bpf_cgroup_dev_ctx अणु
	/* access_type encoded as (BPF_DEVCG_ACC_* << 16) | BPF_DEVCG_DEV_* */
	__u32 access_type;
	__u32 major;
	__u32 minor;
पूर्ण;

काष्ठा bpf_raw_tracepoपूर्णांक_args अणु
	__u64 args[0];
पूर्ण;

/* सूचीECT:  Skip the FIB rules and go to FIB table associated with device
 * OUTPUT:  Do lookup from egress perspective; शेष is ingress
 */
क्रमागत अणु
	BPF_FIB_LOOKUP_सूचीECT  = (1U << 0),
	BPF_FIB_LOOKUP_OUTPUT  = (1U << 1),
पूर्ण;

क्रमागत अणु
	BPF_FIB_LKUP_RET_SUCCESS,      /* lookup successful */
	BPF_FIB_LKUP_RET_BLACKHOLE,    /* dest is blackholed; can be dropped */
	BPF_FIB_LKUP_RET_UNREACHABLE,  /* dest is unreachable; can be dropped */
	BPF_FIB_LKUP_RET_PROHIBIT,     /* dest not allowed; can be dropped */
	BPF_FIB_LKUP_RET_NOT_FWDED,    /* packet is not क्रमwarded */
	BPF_FIB_LKUP_RET_FWD_DISABLED, /* fwding is not enabled on ingress */
	BPF_FIB_LKUP_RET_UNSUPP_LWT,   /* fwd requires encapsulation */
	BPF_FIB_LKUP_RET_NO_NEIGH,     /* no neighbor entry क्रम nh */
	BPF_FIB_LKUP_RET_FRAG_NEEDED,  /* fragmentation required to fwd */
पूर्ण;

काष्ठा bpf_fib_lookup अणु
	/* input:  network family क्रम lookup (AF_INET, AF_INET6)
	 * output: network family of egress nexthop
	 */
	__u8	family;

	/* set अगर lookup is to consider L4 data - e.g., FIB rules */
	__u8	l4_protocol;
	__be16	sport;
	__be16	dport;

	जोड़ अणु	/* used क्रम MTU check */
		/* input to lookup */
		__u16	tot_len; /* L3 length from network hdr (iph->tot_len) */

		/* output: MTU value */
		__u16	mtu_result;
	पूर्ण;
	/* input: L3 device index क्रम lookup
	 * output: device index from FIB lookup
	 */
	__u32	अगरindex;

	जोड़ अणु
		/* inमाला_दो to lookup */
		__u8	tos;		/* AF_INET  */
		__be32	flowinfo;	/* AF_INET6, flow_label + priority */

		/* output: metric of fib result (IPv4/IPv6 only) */
		__u32	rt_metric;
	पूर्ण;

	जोड़ अणु
		__be32		ipv4_src;
		__u32		ipv6_src[4];  /* in6_addr; network order */
	पूर्ण;

	/* input to bpf_fib_lookup, ipvअणु4,6पूर्ण_dst is destination address in
	 * network header. output: bpf_fib_lookup sets to gateway address
	 * अगर FIB lookup वापसs gateway route
	 */
	जोड़ अणु
		__be32		ipv4_dst;
		__u32		ipv6_dst[4];  /* in6_addr; network order */
	पूर्ण;

	/* output */
	__be16	h_vlan_proto;
	__be16	h_vlan_TCI;
	__u8	smac[6];     /* ETH_ALEN */
	__u8	dmac[6];     /* ETH_ALEN */
पूर्ण;

काष्ठा bpf_redir_neigh अणु
	/* network family क्रम lookup (AF_INET, AF_INET6) */
	__u32 nh_family;
	/* network address of nexthop; skips fib lookup to find gateway */
	जोड़ अणु
		__be32		ipv4_nh;
		__u32		ipv6_nh[4];  /* in6_addr; network order */
	पूर्ण;
पूर्ण;

/* bpf_check_mtu flags*/
क्रमागत  bpf_check_mtu_flags अणु
	BPF_MTU_CHK_SEGS  = (1U << 0),
पूर्ण;

क्रमागत bpf_check_mtu_ret अणु
	BPF_MTU_CHK_RET_SUCCESS,      /* check and lookup successful */
	BPF_MTU_CHK_RET_FRAG_NEEDED,  /* fragmentation required to fwd */
	BPF_MTU_CHK_RET_SEGS_TOOBIG,  /* GSO re-segmentation needed to fwd */
पूर्ण;

क्रमागत bpf_task_fd_type अणु
	BPF_FD_TYPE_RAW_TRACEPOINT,	/* tp name */
	BPF_FD_TYPE_TRACEPOINT,		/* tp name */
	BPF_FD_TYPE_KPROBE,		/* (symbol + offset) or addr */
	BPF_FD_TYPE_KRETPROBE,		/* (symbol + offset) or addr */
	BPF_FD_TYPE_UPROBE,		/* filename + offset */
	BPF_FD_TYPE_URETPROBE,		/* filename + offset */
पूर्ण;

क्रमागत अणु
	BPF_FLOW_DISSECTOR_F_PARSE_1ST_FRAG		= (1U << 0),
	BPF_FLOW_DISSECTOR_F_STOP_AT_FLOW_LABEL		= (1U << 1),
	BPF_FLOW_DISSECTOR_F_STOP_AT_ENCAP		= (1U << 2),
पूर्ण;

काष्ठा bpf_flow_keys अणु
	__u16	nhoff;
	__u16	thoff;
	__u16	addr_proto;			/* ETH_P_* of valid addrs */
	__u8	is_frag;
	__u8	is_first_frag;
	__u8	is_encap;
	__u8	ip_proto;
	__be16	n_proto;
	__be16	sport;
	__be16	dport;
	जोड़ अणु
		काष्ठा अणु
			__be32	ipv4_src;
			__be32	ipv4_dst;
		पूर्ण;
		काष्ठा अणु
			__u32	ipv6_src[4];	/* in6_addr; network order */
			__u32	ipv6_dst[4];	/* in6_addr; network order */
		पूर्ण;
	पूर्ण;
	__u32	flags;
	__be32	flow_label;
पूर्ण;

काष्ठा bpf_func_info अणु
	__u32	insn_off;
	__u32	type_id;
पूर्ण;

#घोषणा BPF_LINE_INFO_LINE_NUM(line_col)	((line_col) >> 10)
#घोषणा BPF_LINE_INFO_LINE_COL(line_col)	((line_col) & 0x3ff)

काष्ठा bpf_line_info अणु
	__u32	insn_off;
	__u32	file_name_off;
	__u32	line_off;
	__u32	line_col;
पूर्ण;

काष्ठा bpf_spin_lock अणु
	__u32	val;
पूर्ण;

काष्ठा bpf_sysctl अणु
	__u32	ग_लिखो;		/* Sysctl is being पढ़ो (= 0) or written (= 1).
				 * Allows 1,2,4-byte पढ़ो, but no ग_लिखो.
				 */
	__u32	file_pos;	/* Sysctl file position to पढ़ो from, ग_लिखो to.
				 * Allows 1,2,4-byte पढ़ो an 4-byte ग_लिखो.
				 */
पूर्ण;

काष्ठा bpf_sockopt अणु
	__bpf_md_ptr(काष्ठा bpf_sock *, sk);
	__bpf_md_ptr(व्योम *, optval);
	__bpf_md_ptr(व्योम *, optval_end);

	__s32	level;
	__s32	optname;
	__s32	optlen;
	__s32	retval;
पूर्ण;

काष्ठा bpf_pidns_info अणु
	__u32 pid;
	__u32 tgid;
पूर्ण;

/* User accessible data क्रम SK_LOOKUP programs. Add new fields at the end. */
काष्ठा bpf_sk_lookup अणु
	जोड़ अणु
		__bpf_md_ptr(काष्ठा bpf_sock *, sk); /* Selected socket */
		__u64 cookie; /* Non-zero अगर socket was selected in PROG_TEST_RUN */
	पूर्ण;

	__u32 family;		/* Protocol family (AF_INET, AF_INET6) */
	__u32 protocol;		/* IP protocol (IPPROTO_TCP, IPPROTO_UDP) */
	__u32 remote_ip4;	/* Network byte order */
	__u32 remote_ip6[4];	/* Network byte order */
	__u32 remote_port;	/* Network byte order */
	__u32 local_ip4;	/* Network byte order */
	__u32 local_ip6[4];	/* Network byte order */
	__u32 local_port;	/* Host byte order */
पूर्ण;

/*
 * काष्ठा btf_ptr is used क्रम typed poपूर्णांकer representation; the
 * type id is used to render the poपूर्णांकer data as the appropriate type
 * via the bpf_snम_लिखो_btf() helper described above.  A flags field -
 * potentially to specअगरy additional details about the BTF poपूर्णांकer
 * (rather than its mode of display) - is included क्रम future use.
 * Display flags - BTF_F_* - are passed to bpf_snम_लिखो_btf separately.
 */
काष्ठा btf_ptr अणु
	व्योम *ptr;
	__u32 type_id;
	__u32 flags;		/* BTF ptr flags; unused at present. */
पूर्ण;

/*
 * Flags to control bpf_snम_लिखो_btf() behaviour.
 *     - BTF_F_COMPACT: no क्रमmatting around type inक्रमmation
 *     - BTF_F_NONAME: no काष्ठा/जोड़ member names/types
 *     - BTF_F_PTR_RAW: show raw (unobfuscated) poपूर्णांकer values;
 *       equivalent to %px.
 *     - BTF_F_ZERO: show zero-valued काष्ठा/जोड़ members; they
 *       are not displayed by शेष
 */
क्रमागत अणु
	BTF_F_COMPACT	=	(1ULL << 0),
	BTF_F_NONAME	=	(1ULL << 1),
	BTF_F_PTR_RAW	=	(1ULL << 2),
	BTF_F_ZERO	=	(1ULL << 3),
पूर्ण;

#पूर्ण_अगर /* _UAPI__LINUX_BPF_H__ */
