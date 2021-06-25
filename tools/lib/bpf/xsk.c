<शैली गुरु>
// SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause)

/*
 * AF_XDP user-space access library.
 *
 * Copyright(c) 2018 - 2019 Intel Corporation.
 *
 * Author(s): Magnus Karlsson <magnus.karlsson@पूर्णांकel.com>
 */

#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <माला.स>
#समावेश <unistd.h>
#समावेश <arpa/inet.h>
#समावेश <यंत्र/barrier.h>
#समावेश <linux/compiler.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/filter.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_packet.h>
#समावेश <linux/अगर_xdp.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/sockios.h>
#समावेश <net/अगर.h>
#समावेश <sys/ioctl.h>
#समावेश <sys/mman.h>
#समावेश <sys/socket.h>
#समावेश <sys/types.h>
#समावेश <linux/अगर_link.h>

#समावेश "bpf.h"
#समावेश "libbpf.h"
#समावेश "libbpf_internal.h"
#समावेश "xsk.h"

#अगर_अघोषित SOL_XDP
 #घोषणा SOL_XDP 283
#पूर्ण_अगर

#अगर_अघोषित AF_XDP
 #घोषणा AF_XDP 44
#पूर्ण_अगर

#अगर_अघोषित PF_XDP
 #घोषणा PF_XDP AF_XDP
#पूर्ण_अगर

क्रमागत xsk_prog अणु
	XSK_PROG_FALLBACK,
	XSK_PROG_REसूचीECT_FLAGS,
पूर्ण;

काष्ठा xsk_umem अणु
	काष्ठा xsk_ring_prod *fill_save;
	काष्ठा xsk_ring_cons *comp_save;
	अक्षर *umem_area;
	काष्ठा xsk_umem_config config;
	पूर्णांक fd;
	पूर्णांक refcount;
	काष्ठा list_head ctx_list;
	bool rx_ring_setup_करोne;
	bool tx_ring_setup_करोne;
पूर्ण;

काष्ठा xsk_ctx अणु
	काष्ठा xsk_ring_prod *fill;
	काष्ठा xsk_ring_cons *comp;
	__u32 queue_id;
	काष्ठा xsk_umem *umem;
	पूर्णांक refcount;
	पूर्णांक अगरindex;
	काष्ठा list_head list;
	पूर्णांक prog_fd;
	पूर्णांक link_fd;
	पूर्णांक xsks_map_fd;
	अक्षर अगरname[IFNAMSIZ];
	bool has_bpf_link;
पूर्ण;

काष्ठा xsk_socket अणु
	काष्ठा xsk_ring_cons *rx;
	काष्ठा xsk_ring_prod *tx;
	__u64 outstanding_tx;
	काष्ठा xsk_ctx *ctx;
	काष्ठा xsk_socket_config config;
	पूर्णांक fd;
पूर्ण;

काष्ठा xsk_nl_info अणु
	bool xdp_prog_attached;
	पूर्णांक अगरindex;
	पूर्णांक fd;
पूर्ण;

/* Up until and including Linux 5.3 */
काष्ठा xdp_ring_offset_v1 अणु
	__u64 producer;
	__u64 consumer;
	__u64 desc;
पूर्ण;

/* Up until and including Linux 5.3 */
काष्ठा xdp_mmap_offsets_v1 अणु
	काष्ठा xdp_ring_offset_v1 rx;
	काष्ठा xdp_ring_offset_v1 tx;
	काष्ठा xdp_ring_offset_v1 fr;
	काष्ठा xdp_ring_offset_v1 cr;
पूर्ण;

पूर्णांक xsk_umem__fd(स्थिर काष्ठा xsk_umem *umem)
अणु
	वापस umem ? umem->fd : -EINVAL;
पूर्ण

पूर्णांक xsk_socket__fd(स्थिर काष्ठा xsk_socket *xsk)
अणु
	वापस xsk ? xsk->fd : -EINVAL;
पूर्ण

अटल bool xsk_page_aligned(व्योम *buffer)
अणु
	अचिन्हित दीर्घ addr = (अचिन्हित दीर्घ)buffer;

	वापस !(addr & (getpagesize() - 1));
पूर्ण

अटल व्योम xsk_set_umem_config(काष्ठा xsk_umem_config *cfg,
				स्थिर काष्ठा xsk_umem_config *usr_cfg)
अणु
	अगर (!usr_cfg) अणु
		cfg->fill_size = XSK_RING_PROD__DEFAULT_NUM_DESCS;
		cfg->comp_size = XSK_RING_CONS__DEFAULT_NUM_DESCS;
		cfg->frame_size = XSK_UMEM__DEFAULT_FRAME_SIZE;
		cfg->frame_headroom = XSK_UMEM__DEFAULT_FRAME_HEADROOM;
		cfg->flags = XSK_UMEM__DEFAULT_FLAGS;
		वापस;
	पूर्ण

	cfg->fill_size = usr_cfg->fill_size;
	cfg->comp_size = usr_cfg->comp_size;
	cfg->frame_size = usr_cfg->frame_size;
	cfg->frame_headroom = usr_cfg->frame_headroom;
	cfg->flags = usr_cfg->flags;
पूर्ण

अटल पूर्णांक xsk_set_xdp_socket_config(काष्ठा xsk_socket_config *cfg,
				     स्थिर काष्ठा xsk_socket_config *usr_cfg)
अणु
	अगर (!usr_cfg) अणु
		cfg->rx_size = XSK_RING_CONS__DEFAULT_NUM_DESCS;
		cfg->tx_size = XSK_RING_PROD__DEFAULT_NUM_DESCS;
		cfg->libbpf_flags = 0;
		cfg->xdp_flags = 0;
		cfg->bind_flags = 0;
		वापस 0;
	पूर्ण

	अगर (usr_cfg->libbpf_flags & ~XSK_LIBBPF_FLAGS__INHIBIT_PROG_LOAD)
		वापस -EINVAL;

	cfg->rx_size = usr_cfg->rx_size;
	cfg->tx_size = usr_cfg->tx_size;
	cfg->libbpf_flags = usr_cfg->libbpf_flags;
	cfg->xdp_flags = usr_cfg->xdp_flags;
	cfg->bind_flags = usr_cfg->bind_flags;

	वापस 0;
पूर्ण

अटल व्योम xsk_mmap_offsets_v1(काष्ठा xdp_mmap_offsets *off)
अणु
	काष्ठा xdp_mmap_offsets_v1 off_v1;

	/* माला_लोockopt on a kernel <= 5.3 has no flags fields.
	 * Copy over the offsets to the correct places in the >=5.4 क्रमmat
	 * and put the flags where they would have been on that kernel.
	 */
	स_नकल(&off_v1, off, माप(off_v1));

	off->rx.producer = off_v1.rx.producer;
	off->rx.consumer = off_v1.rx.consumer;
	off->rx.desc = off_v1.rx.desc;
	off->rx.flags = off_v1.rx.consumer + माप(__u32);

	off->tx.producer = off_v1.tx.producer;
	off->tx.consumer = off_v1.tx.consumer;
	off->tx.desc = off_v1.tx.desc;
	off->tx.flags = off_v1.tx.consumer + माप(__u32);

	off->fr.producer = off_v1.fr.producer;
	off->fr.consumer = off_v1.fr.consumer;
	off->fr.desc = off_v1.fr.desc;
	off->fr.flags = off_v1.fr.consumer + माप(__u32);

	off->cr.producer = off_v1.cr.producer;
	off->cr.consumer = off_v1.cr.consumer;
	off->cr.desc = off_v1.cr.desc;
	off->cr.flags = off_v1.cr.consumer + माप(__u32);
पूर्ण

अटल पूर्णांक xsk_get_mmap_offsets(पूर्णांक fd, काष्ठा xdp_mmap_offsets *off)
अणु
	socklen_t optlen;
	पूर्णांक err;

	optlen = माप(*off);
	err = माला_लोockopt(fd, SOL_XDP, XDP_MMAP_OFFSETS, off, &optlen);
	अगर (err)
		वापस err;

	अगर (optlen == माप(*off))
		वापस 0;

	अगर (optlen == माप(काष्ठा xdp_mmap_offsets_v1)) अणु
		xsk_mmap_offsets_v1(off);
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक xsk_create_umem_rings(काष्ठा xsk_umem *umem, पूर्णांक fd,
				 काष्ठा xsk_ring_prod *fill,
				 काष्ठा xsk_ring_cons *comp)
अणु
	काष्ठा xdp_mmap_offsets off;
	व्योम *map;
	पूर्णांक err;

	err = setsockopt(fd, SOL_XDP, XDP_UMEM_FILL_RING,
			 &umem->config.fill_size,
			 माप(umem->config.fill_size));
	अगर (err)
		वापस -त्रुटि_सं;

	err = setsockopt(fd, SOL_XDP, XDP_UMEM_COMPLETION_RING,
			 &umem->config.comp_size,
			 माप(umem->config.comp_size));
	अगर (err)
		वापस -त्रुटि_सं;

	err = xsk_get_mmap_offsets(fd, &off);
	अगर (err)
		वापस -त्रुटि_सं;

	map = mmap(शून्य, off.fr.desc + umem->config.fill_size * माप(__u64),
		   PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, fd,
		   XDP_UMEM_PGOFF_FILL_RING);
	अगर (map == MAP_FAILED)
		वापस -त्रुटि_सं;

	fill->mask = umem->config.fill_size - 1;
	fill->size = umem->config.fill_size;
	fill->producer = map + off.fr.producer;
	fill->consumer = map + off.fr.consumer;
	fill->flags = map + off.fr.flags;
	fill->ring = map + off.fr.desc;
	fill->cached_cons = umem->config.fill_size;

	map = mmap(शून्य, off.cr.desc + umem->config.comp_size * माप(__u64),
		   PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE, fd,
		   XDP_UMEM_PGOFF_COMPLETION_RING);
	अगर (map == MAP_FAILED) अणु
		err = -त्रुटि_सं;
		जाओ out_mmap;
	पूर्ण

	comp->mask = umem->config.comp_size - 1;
	comp->size = umem->config.comp_size;
	comp->producer = map + off.cr.producer;
	comp->consumer = map + off.cr.consumer;
	comp->flags = map + off.cr.flags;
	comp->ring = map + off.cr.desc;

	वापस 0;

out_mmap:
	munmap(map, off.fr.desc + umem->config.fill_size * माप(__u64));
	वापस err;
पूर्ण

पूर्णांक xsk_umem__create_v0_0_4(काष्ठा xsk_umem **umem_ptr, व्योम *umem_area,
			    __u64 size, काष्ठा xsk_ring_prod *fill,
			    काष्ठा xsk_ring_cons *comp,
			    स्थिर काष्ठा xsk_umem_config *usr_config)
अणु
	काष्ठा xdp_umem_reg mr;
	काष्ठा xsk_umem *umem;
	पूर्णांक err;

	अगर (!umem_area || !umem_ptr || !fill || !comp)
		वापस -EFAULT;
	अगर (!size && !xsk_page_aligned(umem_area))
		वापस -EINVAL;

	umem = सुस्मृति(1, माप(*umem));
	अगर (!umem)
		वापस -ENOMEM;

	umem->fd = socket(AF_XDP, SOCK_RAW, 0);
	अगर (umem->fd < 0) अणु
		err = -त्रुटि_सं;
		जाओ out_umem_alloc;
	पूर्ण

	umem->umem_area = umem_area;
	INIT_LIST_HEAD(&umem->ctx_list);
	xsk_set_umem_config(&umem->config, usr_config);

	स_रखो(&mr, 0, माप(mr));
	mr.addr = (uपूर्णांकptr_t)umem_area;
	mr.len = size;
	mr.chunk_size = umem->config.frame_size;
	mr.headroom = umem->config.frame_headroom;
	mr.flags = umem->config.flags;

	err = setsockopt(umem->fd, SOL_XDP, XDP_UMEM_REG, &mr, माप(mr));
	अगर (err) अणु
		err = -त्रुटि_सं;
		जाओ out_socket;
	पूर्ण

	err = xsk_create_umem_rings(umem, umem->fd, fill, comp);
	अगर (err)
		जाओ out_socket;

	umem->fill_save = fill;
	umem->comp_save = comp;
	*umem_ptr = umem;
	वापस 0;

out_socket:
	बंद(umem->fd);
out_umem_alloc:
	मुक्त(umem);
	वापस err;
पूर्ण

काष्ठा xsk_umem_config_v1 अणु
	__u32 fill_size;
	__u32 comp_size;
	__u32 frame_size;
	__u32 frame_headroom;
पूर्ण;

पूर्णांक xsk_umem__create_v0_0_2(काष्ठा xsk_umem **umem_ptr, व्योम *umem_area,
			    __u64 size, काष्ठा xsk_ring_prod *fill,
			    काष्ठा xsk_ring_cons *comp,
			    स्थिर काष्ठा xsk_umem_config *usr_config)
अणु
	काष्ठा xsk_umem_config config;

	स_नकल(&config, usr_config, माप(काष्ठा xsk_umem_config_v1));
	config.flags = 0;

	वापस xsk_umem__create_v0_0_4(umem_ptr, umem_area, size, fill, comp,
					&config);
पूर्ण
COMPAT_VERSION(xsk_umem__create_v0_0_2, xsk_umem__create, LIBBPF_0.0.2)
DEFAULT_VERSION(xsk_umem__create_v0_0_4, xsk_umem__create, LIBBPF_0.0.4)

अटल क्रमागत xsk_prog get_xsk_prog(व्योम)
अणु
	क्रमागत xsk_prog detected = XSK_PROG_FALLBACK;
	काष्ठा bpf_load_program_attr prog_attr;
	काष्ठा bpf_create_map_attr map_attr;
	__u32 size_out, retval, duration;
	अक्षर data_in = 0, data_out;
	काष्ठा bpf_insn insns[] = अणु
		BPF_LD_MAP_FD(BPF_REG_1, 0),
		BPF_MOV64_IMM(BPF_REG_2, 0),
		BPF_MOV64_IMM(BPF_REG_3, XDP_PASS),
		BPF_EMIT_CALL(BPF_FUNC_redirect_map),
		BPF_EXIT_INSN(),
	पूर्ण;
	पूर्णांक prog_fd, map_fd, ret;

	स_रखो(&map_attr, 0, माप(map_attr));
	map_attr.map_type = BPF_MAP_TYPE_XSKMAP;
	map_attr.key_size = माप(पूर्णांक);
	map_attr.value_size = माप(पूर्णांक);
	map_attr.max_entries = 1;

	map_fd = bpf_create_map_xattr(&map_attr);
	अगर (map_fd < 0)
		वापस detected;

	insns[0].imm = map_fd;

	स_रखो(&prog_attr, 0, माप(prog_attr));
	prog_attr.prog_type = BPF_PROG_TYPE_XDP;
	prog_attr.insns = insns;
	prog_attr.insns_cnt = ARRAY_SIZE(insns);
	prog_attr.license = "GPL";

	prog_fd = bpf_load_program_xattr(&prog_attr, शून्य, 0);
	अगर (prog_fd < 0) अणु
		बंद(map_fd);
		वापस detected;
	पूर्ण

	ret = bpf_prog_test_run(prog_fd, 0, &data_in, 1, &data_out, &size_out, &retval, &duration);
	अगर (!ret && retval == XDP_PASS)
		detected = XSK_PROG_REसूचीECT_FLAGS;
	बंद(prog_fd);
	बंद(map_fd);
	वापस detected;
पूर्ण

अटल पूर्णांक xsk_load_xdp_prog(काष्ठा xsk_socket *xsk)
अणु
	अटल स्थिर पूर्णांक log_buf_size = 16 * 1024;
	काष्ठा xsk_ctx *ctx = xsk->ctx;
	अक्षर log_buf[log_buf_size];
	पूर्णांक prog_fd;

	/* This is the fallback C-program:
	 * SEC("xdp_sock") पूर्णांक xdp_sock_prog(काष्ठा xdp_md *ctx)
	 * अणु
	 *     पूर्णांक ret, index = ctx->rx_queue_index;
	 *
	 *     // A set entry here means that the correspnding queue_id
	 *     // has an active AF_XDP socket bound to it.
	 *     ret = bpf_redirect_map(&xsks_map, index, XDP_PASS);
	 *     अगर (ret > 0)
	 *         वापस ret;
	 *
	 *     // Fallback क्रम pre-5.3 kernels, not supporting शेष
	 *     // action in the flags parameter.
	 *     अगर (bpf_map_lookup_elem(&xsks_map, &index))
	 *         वापस bpf_redirect_map(&xsks_map, index, 0);
	 *     वापस XDP_PASS;
	 * पूर्ण
	 */
	काष्ठा bpf_insn prog[] = अणु
		/* r2 = *(u32 *)(r1 + 16) */
		BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 16),
		/* *(u32 *)(r10 - 4) = r2 */
		BPF_STX_MEM(BPF_W, BPF_REG_10, BPF_REG_2, -4),
		/* r1 = xskmap[] */
		BPF_LD_MAP_FD(BPF_REG_1, ctx->xsks_map_fd),
		/* r3 = XDP_PASS */
		BPF_MOV64_IMM(BPF_REG_3, 2),
		/* call bpf_redirect_map */
		BPF_EMIT_CALL(BPF_FUNC_redirect_map),
		/* अगर w0 != 0 जाओ pc+13 */
		BPF_JMP32_IMM(BPF_JSGT, BPF_REG_0, 0, 13),
		/* r2 = r10 */
		BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
		/* r2 += -4 */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -4),
		/* r1 = xskmap[] */
		BPF_LD_MAP_FD(BPF_REG_1, ctx->xsks_map_fd),
		/* call bpf_map_lookup_elem */
		BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),
		/* r1 = r0 */
		BPF_MOV64_REG(BPF_REG_1, BPF_REG_0),
		/* r0 = XDP_PASS */
		BPF_MOV64_IMM(BPF_REG_0, 2),
		/* अगर r1 == 0 जाओ pc+5 */
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, 5),
		/* r2 = *(u32 *)(r10 - 4) */
		BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_10, -4),
		/* r1 = xskmap[] */
		BPF_LD_MAP_FD(BPF_REG_1, ctx->xsks_map_fd),
		/* r3 = 0 */
		BPF_MOV64_IMM(BPF_REG_3, 0),
		/* call bpf_redirect_map */
		BPF_EMIT_CALL(BPF_FUNC_redirect_map),
		/* The jumps are to this inकाष्ठाion */
		BPF_EXIT_INSN(),
	पूर्ण;

	/* This is the post-5.3 kernel C-program:
	 * SEC("xdp_sock") पूर्णांक xdp_sock_prog(काष्ठा xdp_md *ctx)
	 * अणु
	 *     वापस bpf_redirect_map(&xsks_map, ctx->rx_queue_index, XDP_PASS);
	 * पूर्ण
	 */
	काष्ठा bpf_insn prog_redirect_flags[] = अणु
		/* r2 = *(u32 *)(r1 + 16) */
		BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 16),
		/* r1 = xskmap[] */
		BPF_LD_MAP_FD(BPF_REG_1, ctx->xsks_map_fd),
		/* r3 = XDP_PASS */
		BPF_MOV64_IMM(BPF_REG_3, 2),
		/* call bpf_redirect_map */
		BPF_EMIT_CALL(BPF_FUNC_redirect_map),
		BPF_EXIT_INSN(),
	पूर्ण;
	माप_प्रकार insns_cnt[] = अणुमाप(prog) / माप(काष्ठा bpf_insn),
			      माप(prog_redirect_flags) / माप(काष्ठा bpf_insn),
	पूर्ण;
	काष्ठा bpf_insn *progs[] = अणुprog, prog_redirect_flagsपूर्ण;
	क्रमागत xsk_prog option = get_xsk_prog();

	prog_fd = bpf_load_program(BPF_PROG_TYPE_XDP, progs[option], insns_cnt[option],
				   "LGPL-2.1 or BSD-2-Clause", 0, log_buf,
				   log_buf_size);
	अगर (prog_fd < 0) अणु
		pr_warn("BPF log buffer:\n%s", log_buf);
		वापस prog_fd;
	पूर्ण

	ctx->prog_fd = prog_fd;
	वापस 0;
पूर्ण

अटल पूर्णांक xsk_create_bpf_link(काष्ठा xsk_socket *xsk)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, opts);
	काष्ठा xsk_ctx *ctx = xsk->ctx;
	__u32 prog_id = 0;
	पूर्णांक link_fd;
	पूर्णांक err;

	err = bpf_get_link_xdp_id(ctx->अगरindex, &prog_id, xsk->config.xdp_flags);
	अगर (err) अणु
		pr_warn("getting XDP prog id failed\n");
		वापस err;
	पूर्ण

	/* अगर there's a netlink-based XDP prog loaded on पूर्णांकerface, bail out
	 * and ask user to करो the removal by himself
	 */
	अगर (prog_id) अणु
		pr_warn("Netlink-based XDP prog detected, please unload it in order to launch AF_XDP prog\n");
		वापस -EINVAL;
	पूर्ण

	opts.flags = xsk->config.xdp_flags & ~(XDP_FLAGS_UPDATE_IF_NOEXIST | XDP_FLAGS_REPLACE);

	link_fd = bpf_link_create(ctx->prog_fd, ctx->अगरindex, BPF_XDP, &opts);
	अगर (link_fd < 0) अणु
		pr_warn("bpf_link_create failed: %s\n", म_त्रुटि(त्रुटि_सं));
		वापस link_fd;
	पूर्ण

	ctx->link_fd = link_fd;
	वापस 0;
पूर्ण

अटल पूर्णांक xsk_get_max_queues(काष्ठा xsk_socket *xsk)
अणु
	काष्ठा ethtool_channels channels = अणु .cmd = ETHTOOL_GCHANNELS पूर्ण;
	काष्ठा xsk_ctx *ctx = xsk->ctx;
	काष्ठा अगरreq अगरr = अणुपूर्ण;
	पूर्णांक fd, err, ret;

	fd = socket(AF_LOCAL, SOCK_DGRAM, 0);
	अगर (fd < 0)
		वापस -त्रुटि_सं;

	अगरr.अगरr_data = (व्योम *)&channels;
	स_नकल(अगरr.अगरr_name, ctx->अगरname, IFNAMSIZ - 1);
	अगरr.अगरr_name[IFNAMSIZ - 1] = '\0';
	err = ioctl(fd, SIOCETHTOOL, &अगरr);
	अगर (err && त्रुटि_सं != EOPNOTSUPP) अणु
		ret = -त्रुटि_सं;
		जाओ out;
	पूर्ण

	अगर (err) अणु
		/* If the device says it has no channels, then all traffic
		 * is sent to a single stream, so max queues = 1.
		 */
		ret = 1;
	पूर्ण अन्यथा अणु
		/* Take the max of rx, tx, combined. Drivers वापस
		 * the number of channels in dअगरferent ways.
		 */
		ret = max(channels.max_rx, channels.max_tx);
		ret = max(ret, (पूर्णांक)channels.max_combined);
	पूर्ण

out:
	बंद(fd);
	वापस ret;
पूर्ण

अटल पूर्णांक xsk_create_bpf_maps(काष्ठा xsk_socket *xsk)
अणु
	काष्ठा xsk_ctx *ctx = xsk->ctx;
	पूर्णांक max_queues;
	पूर्णांक fd;

	max_queues = xsk_get_max_queues(xsk);
	अगर (max_queues < 0)
		वापस max_queues;

	fd = bpf_create_map_name(BPF_MAP_TYPE_XSKMAP, "xsks_map",
				 माप(पूर्णांक), माप(पूर्णांक), max_queues, 0);
	अगर (fd < 0)
		वापस fd;

	ctx->xsks_map_fd = fd;

	वापस 0;
पूर्ण

अटल व्योम xsk_delete_bpf_maps(काष्ठा xsk_socket *xsk)
अणु
	काष्ठा xsk_ctx *ctx = xsk->ctx;

	bpf_map_delete_elem(ctx->xsks_map_fd, &ctx->queue_id);
	बंद(ctx->xsks_map_fd);
पूर्ण

अटल पूर्णांक xsk_lookup_bpf_maps(काष्ठा xsk_socket *xsk)
अणु
	__u32 i, *map_ids, num_maps, prog_len = माप(काष्ठा bpf_prog_info);
	__u32 map_len = माप(काष्ठा bpf_map_info);
	काष्ठा bpf_prog_info prog_info = अणुपूर्ण;
	काष्ठा xsk_ctx *ctx = xsk->ctx;
	काष्ठा bpf_map_info map_info;
	पूर्णांक fd, err;

	err = bpf_obj_get_info_by_fd(ctx->prog_fd, &prog_info, &prog_len);
	अगर (err)
		वापस err;

	num_maps = prog_info.nr_map_ids;

	map_ids = सुस्मृति(prog_info.nr_map_ids, माप(*map_ids));
	अगर (!map_ids)
		वापस -ENOMEM;

	स_रखो(&prog_info, 0, prog_len);
	prog_info.nr_map_ids = num_maps;
	prog_info.map_ids = (__u64)(अचिन्हित दीर्घ)map_ids;

	err = bpf_obj_get_info_by_fd(ctx->prog_fd, &prog_info, &prog_len);
	अगर (err)
		जाओ out_map_ids;

	ctx->xsks_map_fd = -1;

	क्रम (i = 0; i < prog_info.nr_map_ids; i++) अणु
		fd = bpf_map_get_fd_by_id(map_ids[i]);
		अगर (fd < 0)
			जारी;

		स_रखो(&map_info, 0, map_len);
		err = bpf_obj_get_info_by_fd(fd, &map_info, &map_len);
		अगर (err) अणु
			बंद(fd);
			जारी;
		पूर्ण

		अगर (!म_भेदन(map_info.name, "xsks_map", माप(map_info.name))) अणु
			ctx->xsks_map_fd = fd;
			अवरोध;
		पूर्ण

		बंद(fd);
	पूर्ण

	अगर (ctx->xsks_map_fd == -1)
		err = -ENOENT;

out_map_ids:
	मुक्त(map_ids);
	वापस err;
पूर्ण

अटल पूर्णांक xsk_set_bpf_maps(काष्ठा xsk_socket *xsk)
अणु
	काष्ठा xsk_ctx *ctx = xsk->ctx;

	वापस bpf_map_update_elem(ctx->xsks_map_fd, &ctx->queue_id,
				   &xsk->fd, 0);
पूर्ण

अटल पूर्णांक xsk_link_lookup(पूर्णांक अगरindex, __u32 *prog_id, पूर्णांक *link_fd)
अणु
	काष्ठा bpf_link_info link_info;
	__u32 link_len;
	__u32 id = 0;
	पूर्णांक err;
	पूर्णांक fd;

	जबतक (true) अणु
		err = bpf_link_get_next_id(id, &id);
		अगर (err) अणु
			अगर (त्रुटि_सं == ENOENT) अणु
				err = 0;
				अवरोध;
			पूर्ण
			pr_warn("can't get next link: %s\n", म_त्रुटि(त्रुटि_सं));
			अवरोध;
		पूर्ण

		fd = bpf_link_get_fd_by_id(id);
		अगर (fd < 0) अणु
			अगर (त्रुटि_सं == ENOENT)
				जारी;
			pr_warn("can't get link by id (%u): %s\n", id, म_त्रुटि(त्रुटि_सं));
			err = -त्रुटि_सं;
			अवरोध;
		पूर्ण

		link_len = माप(काष्ठा bpf_link_info);
		स_रखो(&link_info, 0, link_len);
		err = bpf_obj_get_info_by_fd(fd, &link_info, &link_len);
		अगर (err) अणु
			pr_warn("can't get link info: %s\n", म_त्रुटि(त्रुटि_सं));
			बंद(fd);
			अवरोध;
		पूर्ण
		अगर (link_info.type == BPF_LINK_TYPE_XDP) अणु
			अगर (link_info.xdp.अगरindex == अगरindex) अणु
				*link_fd = fd;
				अगर (prog_id)
					*prog_id = link_info.prog_id;
				अवरोध;
			पूर्ण
		पूर्ण
		बंद(fd);
	पूर्ण

	वापस err;
पूर्ण

अटल bool xsk_probe_bpf_link(व्योम)
अणु
	DECLARE_LIBBPF_OPTS(bpf_link_create_opts, opts,
			    .flags = XDP_FLAGS_SKB_MODE);
	काष्ठा bpf_load_program_attr prog_attr;
	काष्ठा bpf_insn insns[2] = अणु
		BPF_MOV64_IMM(BPF_REG_0, XDP_PASS),
		BPF_EXIT_INSN()
	पूर्ण;
	पूर्णांक prog_fd, link_fd = -1;
	पूर्णांक अगरindex_lo = 1;
	bool ret = false;
	पूर्णांक err;

	err = xsk_link_lookup(अगरindex_lo, शून्य, &link_fd);
	अगर (err)
		वापस ret;

	अगर (link_fd >= 0)
		वापस true;

	स_रखो(&prog_attr, 0, माप(prog_attr));
	prog_attr.prog_type = BPF_PROG_TYPE_XDP;
	prog_attr.insns = insns;
	prog_attr.insns_cnt = ARRAY_SIZE(insns);
	prog_attr.license = "GPL";

	prog_fd = bpf_load_program_xattr(&prog_attr, शून्य, 0);
	अगर (prog_fd < 0)
		वापस ret;

	link_fd = bpf_link_create(prog_fd, अगरindex_lo, BPF_XDP, &opts);
	बंद(prog_fd);

	अगर (link_fd >= 0) अणु
		ret = true;
		बंद(link_fd);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक xsk_create_xsk_काष्ठा(पूर्णांक अगरindex, काष्ठा xsk_socket *xsk)
अणु
	अक्षर अगरname[IFNAMSIZ];
	काष्ठा xsk_ctx *ctx;
	अक्षर *पूर्णांकerface;

	ctx = सुस्मृति(1, माप(*ctx));
	अगर (!ctx)
		वापस -ENOMEM;

	पूर्णांकerface = अगर_indextoname(अगरindex, &अगरname[0]);
	अगर (!पूर्णांकerface) अणु
		मुक्त(ctx);
		वापस -त्रुटि_सं;
	पूर्ण

	ctx->अगरindex = अगरindex;
	स_नकल(ctx->अगरname, अगरname, IFNAMSIZ -1);
	ctx->अगरname[IFNAMSIZ - 1] = 0;

	xsk->ctx = ctx;
	xsk->ctx->has_bpf_link = xsk_probe_bpf_link();

	वापस 0;
पूर्ण

अटल पूर्णांक xsk_init_xdp_res(काष्ठा xsk_socket *xsk,
			    पूर्णांक *xsks_map_fd)
अणु
	काष्ठा xsk_ctx *ctx = xsk->ctx;
	पूर्णांक err;

	err = xsk_create_bpf_maps(xsk);
	अगर (err)
		वापस err;

	err = xsk_load_xdp_prog(xsk);
	अगर (err)
		जाओ err_load_xdp_prog;

	अगर (ctx->has_bpf_link)
		err = xsk_create_bpf_link(xsk);
	अन्यथा
		err = bpf_set_link_xdp_fd(xsk->ctx->अगरindex, ctx->prog_fd,
					  xsk->config.xdp_flags);

	अगर (err)
		जाओ err_attach_xdp_prog;

	अगर (!xsk->rx)
		वापस err;

	err = xsk_set_bpf_maps(xsk);
	अगर (err)
		जाओ err_set_bpf_maps;

	वापस err;

err_set_bpf_maps:
	अगर (ctx->has_bpf_link)
		बंद(ctx->link_fd);
	अन्यथा
		bpf_set_link_xdp_fd(ctx->अगरindex, -1, 0);
err_attach_xdp_prog:
	बंद(ctx->prog_fd);
err_load_xdp_prog:
	xsk_delete_bpf_maps(xsk);
	वापस err;
पूर्ण

अटल पूर्णांक xsk_lookup_xdp_res(काष्ठा xsk_socket *xsk, पूर्णांक *xsks_map_fd, पूर्णांक prog_id)
अणु
	काष्ठा xsk_ctx *ctx = xsk->ctx;
	पूर्णांक err;

	ctx->prog_fd = bpf_prog_get_fd_by_id(prog_id);
	अगर (ctx->prog_fd < 0) अणु
		err = -त्रुटि_सं;
		जाओ err_prog_fd;
	पूर्ण
	err = xsk_lookup_bpf_maps(xsk);
	अगर (err)
		जाओ err_lookup_maps;

	अगर (!xsk->rx)
		वापस err;

	err = xsk_set_bpf_maps(xsk);
	अगर (err)
		जाओ err_set_maps;

	वापस err;

err_set_maps:
	बंद(ctx->xsks_map_fd);
err_lookup_maps:
	बंद(ctx->prog_fd);
err_prog_fd:
	अगर (ctx->has_bpf_link)
		बंद(ctx->link_fd);
	वापस err;
पूर्ण

अटल पूर्णांक __xsk_setup_xdp_prog(काष्ठा xsk_socket *_xdp, पूर्णांक *xsks_map_fd)
अणु
	काष्ठा xsk_socket *xsk = _xdp;
	काष्ठा xsk_ctx *ctx = xsk->ctx;
	__u32 prog_id = 0;
	पूर्णांक err;

	अगर (ctx->has_bpf_link)
		err = xsk_link_lookup(ctx->अगरindex, &prog_id, &ctx->link_fd);
	अन्यथा
		err = bpf_get_link_xdp_id(ctx->अगरindex, &prog_id, xsk->config.xdp_flags);

	अगर (err)
		वापस err;

	err = !prog_id ? xsk_init_xdp_res(xsk, xsks_map_fd) :
			 xsk_lookup_xdp_res(xsk, xsks_map_fd, prog_id);

	अगर (!err && xsks_map_fd)
		*xsks_map_fd = ctx->xsks_map_fd;

	वापस err;
पूर्ण

अटल काष्ठा xsk_ctx *xsk_get_ctx(काष्ठा xsk_umem *umem, पूर्णांक अगरindex,
				   __u32 queue_id)
अणु
	काष्ठा xsk_ctx *ctx;

	अगर (list_empty(&umem->ctx_list))
		वापस शून्य;

	list_क्रम_each_entry(ctx, &umem->ctx_list, list) अणु
		अगर (ctx->अगरindex == अगरindex && ctx->queue_id == queue_id) अणु
			ctx->refcount++;
			वापस ctx;
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम xsk_put_ctx(काष्ठा xsk_ctx *ctx, bool unmap)
अणु
	काष्ठा xsk_umem *umem = ctx->umem;
	काष्ठा xdp_mmap_offsets off;
	पूर्णांक err;

	अगर (--ctx->refcount)
		वापस;

	अगर (!unmap)
		जाओ out_मुक्त;

	err = xsk_get_mmap_offsets(umem->fd, &off);
	अगर (err)
		जाओ out_मुक्त;

	munmap(ctx->fill->ring - off.fr.desc, off.fr.desc + umem->config.fill_size *
	       माप(__u64));
	munmap(ctx->comp->ring - off.cr.desc, off.cr.desc + umem->config.comp_size *
	       माप(__u64));

out_मुक्त:
	list_del(&ctx->list);
	मुक्त(ctx);
पूर्ण

अटल काष्ठा xsk_ctx *xsk_create_ctx(काष्ठा xsk_socket *xsk,
				      काष्ठा xsk_umem *umem, पूर्णांक अगरindex,
				      स्थिर अक्षर *अगरname, __u32 queue_id,
				      काष्ठा xsk_ring_prod *fill,
				      काष्ठा xsk_ring_cons *comp)
अणु
	काष्ठा xsk_ctx *ctx;
	पूर्णांक err;

	ctx = सुस्मृति(1, माप(*ctx));
	अगर (!ctx)
		वापस शून्य;

	अगर (!umem->fill_save) अणु
		err = xsk_create_umem_rings(umem, xsk->fd, fill, comp);
		अगर (err) अणु
			मुक्त(ctx);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (umem->fill_save != fill || umem->comp_save != comp) अणु
		/* Copy over rings to new काष्ठाs. */
		स_नकल(fill, umem->fill_save, माप(*fill));
		स_नकल(comp, umem->comp_save, माप(*comp));
	पूर्ण

	ctx->अगरindex = अगरindex;
	ctx->refcount = 1;
	ctx->umem = umem;
	ctx->queue_id = queue_id;
	स_नकल(ctx->अगरname, अगरname, IFNAMSIZ - 1);
	ctx->अगरname[IFNAMSIZ - 1] = '\0';

	ctx->fill = fill;
	ctx->comp = comp;
	list_add(&ctx->list, &umem->ctx_list);
	वापस ctx;
पूर्ण

अटल व्योम xsk_destroy_xsk_काष्ठा(काष्ठा xsk_socket *xsk)
अणु
	मुक्त(xsk->ctx);
	मुक्त(xsk);
पूर्ण

पूर्णांक xsk_socket__update_xskmap(काष्ठा xsk_socket *xsk, पूर्णांक fd)
अणु
	xsk->ctx->xsks_map_fd = fd;
	वापस xsk_set_bpf_maps(xsk);
पूर्ण

पूर्णांक xsk_setup_xdp_prog(पूर्णांक अगरindex, पूर्णांक *xsks_map_fd)
अणु
	काष्ठा xsk_socket *xsk;
	पूर्णांक res;

	xsk = सुस्मृति(1, माप(*xsk));
	अगर (!xsk)
		वापस -ENOMEM;

	res = xsk_create_xsk_काष्ठा(अगरindex, xsk);
	अगर (res) अणु
		मुक्त(xsk);
		वापस -EINVAL;
	पूर्ण

	res = __xsk_setup_xdp_prog(xsk, xsks_map_fd);

	xsk_destroy_xsk_काष्ठा(xsk);

	वापस res;
पूर्ण

पूर्णांक xsk_socket__create_shared(काष्ठा xsk_socket **xsk_ptr,
			      स्थिर अक्षर *अगरname,
			      __u32 queue_id, काष्ठा xsk_umem *umem,
			      काष्ठा xsk_ring_cons *rx,
			      काष्ठा xsk_ring_prod *tx,
			      काष्ठा xsk_ring_prod *fill,
			      काष्ठा xsk_ring_cons *comp,
			      स्थिर काष्ठा xsk_socket_config *usr_config)
अणु
	bool unmap, rx_setup_करोne = false, tx_setup_करोne = false;
	व्योम *rx_map = शून्य, *tx_map = शून्य;
	काष्ठा sockaddr_xdp sxdp = अणुपूर्ण;
	काष्ठा xdp_mmap_offsets off;
	काष्ठा xsk_socket *xsk;
	काष्ठा xsk_ctx *ctx;
	पूर्णांक err, अगरindex;

	अगर (!umem || !xsk_ptr || !(rx || tx))
		वापस -EFAULT;

	unmap = umem->fill_save != fill;

	xsk = सुस्मृति(1, माप(*xsk));
	अगर (!xsk)
		वापस -ENOMEM;

	err = xsk_set_xdp_socket_config(&xsk->config, usr_config);
	अगर (err)
		जाओ out_xsk_alloc;

	xsk->outstanding_tx = 0;
	अगरindex = अगर_nametoindex(अगरname);
	अगर (!अगरindex) अणु
		err = -त्रुटि_सं;
		जाओ out_xsk_alloc;
	पूर्ण

	अगर (umem->refcount++ > 0) अणु
		xsk->fd = socket(AF_XDP, SOCK_RAW, 0);
		अगर (xsk->fd < 0) अणु
			err = -त्रुटि_सं;
			जाओ out_xsk_alloc;
		पूर्ण
	पूर्ण अन्यथा अणु
		xsk->fd = umem->fd;
		rx_setup_करोne = umem->rx_ring_setup_करोne;
		tx_setup_करोne = umem->tx_ring_setup_करोne;
	पूर्ण

	ctx = xsk_get_ctx(umem, अगरindex, queue_id);
	अगर (!ctx) अणु
		अगर (!fill || !comp) अणु
			err = -EFAULT;
			जाओ out_socket;
		पूर्ण

		ctx = xsk_create_ctx(xsk, umem, अगरindex, अगरname, queue_id,
				     fill, comp);
		अगर (!ctx) अणु
			err = -ENOMEM;
			जाओ out_socket;
		पूर्ण
	पूर्ण
	xsk->ctx = ctx;
	xsk->ctx->has_bpf_link = xsk_probe_bpf_link();

	अगर (rx && !rx_setup_करोne) अणु
		err = setsockopt(xsk->fd, SOL_XDP, XDP_RX_RING,
				 &xsk->config.rx_size,
				 माप(xsk->config.rx_size));
		अगर (err) अणु
			err = -त्रुटि_सं;
			जाओ out_put_ctx;
		पूर्ण
		अगर (xsk->fd == umem->fd)
			umem->rx_ring_setup_करोne = true;
	पूर्ण
	अगर (tx && !tx_setup_करोne) अणु
		err = setsockopt(xsk->fd, SOL_XDP, XDP_TX_RING,
				 &xsk->config.tx_size,
				 माप(xsk->config.tx_size));
		अगर (err) अणु
			err = -त्रुटि_सं;
			जाओ out_put_ctx;
		पूर्ण
		अगर (xsk->fd == umem->fd)
			umem->tx_ring_setup_करोne = true;
	पूर्ण

	err = xsk_get_mmap_offsets(xsk->fd, &off);
	अगर (err) अणु
		err = -त्रुटि_सं;
		जाओ out_put_ctx;
	पूर्ण

	अगर (rx) अणु
		rx_map = mmap(शून्य, off.rx.desc +
			      xsk->config.rx_size * माप(काष्ठा xdp_desc),
			      PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE,
			      xsk->fd, XDP_PGOFF_RX_RING);
		अगर (rx_map == MAP_FAILED) अणु
			err = -त्रुटि_सं;
			जाओ out_put_ctx;
		पूर्ण

		rx->mask = xsk->config.rx_size - 1;
		rx->size = xsk->config.rx_size;
		rx->producer = rx_map + off.rx.producer;
		rx->consumer = rx_map + off.rx.consumer;
		rx->flags = rx_map + off.rx.flags;
		rx->ring = rx_map + off.rx.desc;
		rx->cached_prod = *rx->producer;
		rx->cached_cons = *rx->consumer;
	पूर्ण
	xsk->rx = rx;

	अगर (tx) अणु
		tx_map = mmap(शून्य, off.tx.desc +
			      xsk->config.tx_size * माप(काष्ठा xdp_desc),
			      PROT_READ | PROT_WRITE, MAP_SHARED | MAP_POPULATE,
			      xsk->fd, XDP_PGOFF_TX_RING);
		अगर (tx_map == MAP_FAILED) अणु
			err = -त्रुटि_सं;
			जाओ out_mmap_rx;
		पूर्ण

		tx->mask = xsk->config.tx_size - 1;
		tx->size = xsk->config.tx_size;
		tx->producer = tx_map + off.tx.producer;
		tx->consumer = tx_map + off.tx.consumer;
		tx->flags = tx_map + off.tx.flags;
		tx->ring = tx_map + off.tx.desc;
		tx->cached_prod = *tx->producer;
		/* cached_cons is r->size bigger than the real consumer poपूर्णांकer
		 * See xsk_prod_nb_मुक्त
		 */
		tx->cached_cons = *tx->consumer + xsk->config.tx_size;
	पूर्ण
	xsk->tx = tx;

	sxdp.sxdp_family = PF_XDP;
	sxdp.sxdp_अगरindex = ctx->अगरindex;
	sxdp.sxdp_queue_id = ctx->queue_id;
	अगर (umem->refcount > 1) अणु
		sxdp.sxdp_flags |= XDP_SHARED_UMEM;
		sxdp.sxdp_shared_umem_fd = umem->fd;
	पूर्ण अन्यथा अणु
		sxdp.sxdp_flags = xsk->config.bind_flags;
	पूर्ण

	err = bind(xsk->fd, (काष्ठा sockaddr *)&sxdp, माप(sxdp));
	अगर (err) अणु
		err = -त्रुटि_सं;
		जाओ out_mmap_tx;
	पूर्ण

	ctx->prog_fd = -1;

	अगर (!(xsk->config.libbpf_flags & XSK_LIBBPF_FLAGS__INHIBIT_PROG_LOAD)) अणु
		err = __xsk_setup_xdp_prog(xsk, शून्य);
		अगर (err)
			जाओ out_mmap_tx;
	पूर्ण

	*xsk_ptr = xsk;
	umem->fill_save = शून्य;
	umem->comp_save = शून्य;
	वापस 0;

out_mmap_tx:
	अगर (tx)
		munmap(tx_map, off.tx.desc +
		       xsk->config.tx_size * माप(काष्ठा xdp_desc));
out_mmap_rx:
	अगर (rx)
		munmap(rx_map, off.rx.desc +
		       xsk->config.rx_size * माप(काष्ठा xdp_desc));
out_put_ctx:
	xsk_put_ctx(ctx, unmap);
out_socket:
	अगर (--umem->refcount)
		बंद(xsk->fd);
out_xsk_alloc:
	मुक्त(xsk);
	वापस err;
पूर्ण

पूर्णांक xsk_socket__create(काष्ठा xsk_socket **xsk_ptr, स्थिर अक्षर *अगरname,
		       __u32 queue_id, काष्ठा xsk_umem *umem,
		       काष्ठा xsk_ring_cons *rx, काष्ठा xsk_ring_prod *tx,
		       स्थिर काष्ठा xsk_socket_config *usr_config)
अणु
	अगर (!umem)
		वापस -EFAULT;

	वापस xsk_socket__create_shared(xsk_ptr, अगरname, queue_id, umem,
					 rx, tx, umem->fill_save,
					 umem->comp_save, usr_config);
पूर्ण

पूर्णांक xsk_umem__delete(काष्ठा xsk_umem *umem)
अणु
	अगर (!umem)
		वापस 0;

	अगर (umem->refcount)
		वापस -EBUSY;

	बंद(umem->fd);
	मुक्त(umem);

	वापस 0;
पूर्ण

व्योम xsk_socket__delete(काष्ठा xsk_socket *xsk)
अणु
	माप_प्रकार desc_sz = माप(काष्ठा xdp_desc);
	काष्ठा xdp_mmap_offsets off;
	काष्ठा xsk_umem *umem;
	काष्ठा xsk_ctx *ctx;
	पूर्णांक err;

	अगर (!xsk)
		वापस;

	ctx = xsk->ctx;
	umem = ctx->umem;
	अगर (ctx->prog_fd != -1) अणु
		xsk_delete_bpf_maps(xsk);
		बंद(ctx->prog_fd);
		अगर (ctx->has_bpf_link)
			बंद(ctx->link_fd);
	पूर्ण

	err = xsk_get_mmap_offsets(xsk->fd, &off);
	अगर (!err) अणु
		अगर (xsk->rx) अणु
			munmap(xsk->rx->ring - off.rx.desc,
			       off.rx.desc + xsk->config.rx_size * desc_sz);
		पूर्ण
		अगर (xsk->tx) अणु
			munmap(xsk->tx->ring - off.tx.desc,
			       off.tx.desc + xsk->config.tx_size * desc_sz);
		पूर्ण
	पूर्ण

	xsk_put_ctx(ctx, true);

	umem->refcount--;
	/* Do not बंद an fd that also has an associated umem connected
	 * to it.
	 */
	अगर (xsk->fd != umem->fd)
		बंद(xsk->fd);
	मुक्त(xsk);
पूर्ण
