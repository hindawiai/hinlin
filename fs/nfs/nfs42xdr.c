<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Anna Schumaker <Anna.Schumaker@Netapp.com>
 */
#अगर_अघोषित __LINUX_FS_NFS_NFS4_2XDR_H
#घोषणा __LINUX_FS_NFS_NFS4_2XDR_H

#समावेश "nfs42.h"

#घोषणा encode_fallocate_maxsz		(encode_stateid_maxsz + \
					 2 /* offset */ + \
					 2 /* length */)
#घोषणा NFS42_WRITE_RES_SIZE		(1 /* wr_callback_id size */ +\
					 XDR_QUADLEN(NFS4_STATEID_SIZE) + \
					 2 /* wr_count */ + \
					 1 /* wr_committed */ + \
					 XDR_QUADLEN(NFS4_VERIFIER_SIZE))
#घोषणा encode_allocate_maxsz		(op_encode_hdr_maxsz + \
					 encode_fallocate_maxsz)
#घोषणा decode_allocate_maxsz		(op_decode_hdr_maxsz)
#घोषणा encode_copy_maxsz		(op_encode_hdr_maxsz +          \
					 XDR_QUADLEN(NFS4_STATEID_SIZE) + \
					 XDR_QUADLEN(NFS4_STATEID_SIZE) + \
					 2 + 2 + 2 + 1 + 1 + 1 +\
					 1 + /* One cnr_source_server */\
					 1 + /* nl4_type */ \
					 1 + XDR_QUADLEN(NFS4_OPAQUE_LIMIT))
#घोषणा decode_copy_maxsz		(op_decode_hdr_maxsz + \
					 NFS42_WRITE_RES_SIZE + \
					 1 /* cr_consecutive */ + \
					 1 /* cr_synchronous */)
#घोषणा encode_offload_cancel_maxsz	(op_encode_hdr_maxsz + \
					 XDR_QUADLEN(NFS4_STATEID_SIZE))
#घोषणा decode_offload_cancel_maxsz	(op_decode_hdr_maxsz)
#घोषणा encode_copy_notअगरy_maxsz	(op_encode_hdr_maxsz + \
					 XDR_QUADLEN(NFS4_STATEID_SIZE) + \
					 1 + /* nl4_type */ \
					 1 + XDR_QUADLEN(NFS4_OPAQUE_LIMIT))
#घोषणा decode_copy_notअगरy_maxsz	(op_decode_hdr_maxsz + \
					 3 + /* cnr_lease_समय */\
					 XDR_QUADLEN(NFS4_STATEID_SIZE) + \
					 1 + /* Support 1 cnr_source_server */\
					 1 + /* nl4_type */ \
					 1 + XDR_QUADLEN(NFS4_OPAQUE_LIMIT))
#घोषणा encode_deallocate_maxsz		(op_encode_hdr_maxsz + \
					 encode_fallocate_maxsz)
#घोषणा decode_deallocate_maxsz		(op_decode_hdr_maxsz)
#घोषणा encode_पढ़ो_plus_maxsz		(op_encode_hdr_maxsz + \
					 encode_stateid_maxsz + 3)
#घोषणा NFS42_READ_PLUS_SEGMENT_SIZE	(1 /* data_content4 */ + \
					 2 /* data_info4.di_offset */ + \
					 2 /* data_info4.di_length */)
#घोषणा decode_पढ़ो_plus_maxsz		(op_decode_hdr_maxsz + \
					 1 /* rpr_eof */ + \
					 1 /* rpr_contents count */ + \
					 2 * NFS42_READ_PLUS_SEGMENT_SIZE)
#घोषणा encode_seek_maxsz		(op_encode_hdr_maxsz + \
					 encode_stateid_maxsz + \
					 2 /* offset */ + \
					 1 /* whence */)
#घोषणा decode_seek_maxsz		(op_decode_hdr_maxsz + \
					 1 /* eof */ + \
					 1 /* whence */ + \
					 2 /* offset */ + \
					 2 /* length */)
#घोषणा encode_io_info_maxsz		4
#घोषणा encode_layoutstats_maxsz	(op_decode_hdr_maxsz + \
					2 /* offset */ + \
					2 /* length */ + \
					encode_stateid_maxsz + \
					encode_io_info_maxsz + \
					encode_io_info_maxsz + \
					1 /* opaque devaddr4 length */ + \
					XDR_QUADLEN(PNFS_LAYOUTSTATS_MAXSIZE))
#घोषणा decode_layoutstats_maxsz	(op_decode_hdr_maxsz)
#घोषणा encode_device_error_maxsz	(XDR_QUADLEN(NFS4_DEVICEID4_SIZE) + \
					1 /* status */ + 1 /* opnum */)
#घोषणा encode_layouterror_maxsz	(op_decode_hdr_maxsz + \
					2 /* offset */ + \
					2 /* length */ + \
					encode_stateid_maxsz + \
					1 /* Array size */ + \
					encode_device_error_maxsz)
#घोषणा decode_layouterror_maxsz	(op_decode_hdr_maxsz)
#घोषणा encode_clone_maxsz		(encode_stateid_maxsz + \
					encode_stateid_maxsz + \
					2 /* src offset */ + \
					2 /* dst offset */ + \
					2 /* count */)
#घोषणा decode_clone_maxsz		(op_decode_hdr_maxsz)

#घोषणा NFS4_enc_allocate_sz		(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_allocate_maxsz + \
					 encode_getattr_maxsz)
#घोषणा NFS4_dec_allocate_sz		(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_allocate_maxsz + \
					 decode_getattr_maxsz)
#घोषणा NFS4_enc_copy_sz		(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_savefh_maxsz + \
					 encode_putfh_maxsz + \
					 encode_copy_maxsz + \
					 encode_commit_maxsz)
#घोषणा NFS4_dec_copy_sz		(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_savefh_maxsz + \
					 decode_putfh_maxsz + \
					 decode_copy_maxsz + \
					 decode_commit_maxsz)
#घोषणा NFS4_enc_offload_cancel_sz	(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_offload_cancel_maxsz)
#घोषणा NFS4_dec_offload_cancel_sz	(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_offload_cancel_maxsz)
#घोषणा NFS4_enc_copy_notअगरy_sz		(compound_encode_hdr_maxsz + \
					 encode_putfh_maxsz + \
					 encode_copy_notअगरy_maxsz)
#घोषणा NFS4_dec_copy_notअगरy_sz		(compound_decode_hdr_maxsz + \
					 decode_putfh_maxsz + \
					 decode_copy_notअगरy_maxsz)
#घोषणा NFS4_enc_deallocate_sz		(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_deallocate_maxsz + \
					 encode_getattr_maxsz)
#घोषणा NFS4_dec_deallocate_sz		(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_deallocate_maxsz + \
					 decode_getattr_maxsz)
#घोषणा NFS4_enc_पढ़ो_plus_sz		(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_पढ़ो_plus_maxsz)
#घोषणा NFS4_dec_पढ़ो_plus_sz		(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_पढ़ो_plus_maxsz)
#घोषणा NFS4_enc_seek_sz		(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_seek_maxsz)
#घोषणा NFS4_dec_seek_sz		(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_seek_maxsz)
#घोषणा NFS4_enc_layoutstats_sz		(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 PNFS_LAYOUTSTATS_MAXDEV * encode_layoutstats_maxsz)
#घोषणा NFS4_dec_layoutstats_sz		(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 PNFS_LAYOUTSTATS_MAXDEV * decode_layoutstats_maxsz)
#घोषणा NFS4_enc_layouterror_sz		(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 NFS42_LAYOUTERROR_MAX * \
					 encode_layouterror_maxsz)
#घोषणा NFS4_dec_layouterror_sz		(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 NFS42_LAYOUTERROR_MAX * \
					 decode_layouterror_maxsz)
#घोषणा NFS4_enc_clone_sz		(compound_encode_hdr_maxsz + \
					 encode_sequence_maxsz + \
					 encode_putfh_maxsz + \
					 encode_savefh_maxsz + \
					 encode_putfh_maxsz + \
					 encode_clone_maxsz + \
					 encode_getattr_maxsz)
#घोषणा NFS4_dec_clone_sz		(compound_decode_hdr_maxsz + \
					 decode_sequence_maxsz + \
					 decode_putfh_maxsz + \
					 decode_savefh_maxsz + \
					 decode_putfh_maxsz + \
					 decode_clone_maxsz + \
					 decode_getattr_maxsz)

/* Not limited by NFS itself, limited by the generic xattr code */
#घोषणा nfs4_xattr_name_maxsz   XDR_QUADLEN(XATTR_NAME_MAX)

#घोषणा encode_getxattr_maxsz   (op_encode_hdr_maxsz + 1 + \
				 nfs4_xattr_name_maxsz)
#घोषणा decode_getxattr_maxsz   (op_decode_hdr_maxsz + 1 + pagepad_maxsz)
#घोषणा encode_setxattr_maxsz   (op_encode_hdr_maxsz + \
				 1 + nfs4_xattr_name_maxsz + 1)
#घोषणा decode_setxattr_maxsz   (op_decode_hdr_maxsz + decode_change_info_maxsz)
#घोषणा encode_listxattrs_maxsz  (op_encode_hdr_maxsz + 2 + 1)
#घोषणा decode_listxattrs_maxsz  (op_decode_hdr_maxsz + 2 + 1 + 1 + 1)
#घोषणा encode_हटाओxattr_maxsz (op_encode_hdr_maxsz + 1 + \
				  nfs4_xattr_name_maxsz)
#घोषणा decode_हटाओxattr_maxsz (op_decode_hdr_maxsz + \
				  decode_change_info_maxsz)

#घोषणा NFS4_enc_getxattr_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_getxattr_maxsz)
#घोषणा NFS4_dec_getxattr_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_getxattr_maxsz)
#घोषणा NFS4_enc_setxattr_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_setxattr_maxsz)
#घोषणा NFS4_dec_setxattr_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_setxattr_maxsz)
#घोषणा NFS4_enc_listxattrs_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_listxattrs_maxsz)
#घोषणा NFS4_dec_listxattrs_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_listxattrs_maxsz)
#घोषणा NFS4_enc_हटाओxattr_sz	(compound_encode_hdr_maxsz + \
				encode_sequence_maxsz + \
				encode_putfh_maxsz + \
				encode_हटाओxattr_maxsz)
#घोषणा NFS4_dec_हटाओxattr_sz	(compound_decode_hdr_maxsz + \
				decode_sequence_maxsz + \
				decode_putfh_maxsz + \
				decode_हटाओxattr_maxsz)

/*
 * These values specअगरy the maximum amount of data that is not
 * associated with the extended attribute name or extended
 * attribute list in the SETXATTR, GETXATTR and LISTXATTR
 * respectively.
 */
स्थिर u32 nfs42_maxsetxattr_overhead = ((RPC_MAX_HEADER_WITH_AUTH +
					compound_encode_hdr_maxsz +
					encode_sequence_maxsz +
					encode_putfh_maxsz + 1 +
					nfs4_xattr_name_maxsz)
					* XDR_UNIT);

स्थिर u32 nfs42_maxgetxattr_overhead = ((RPC_MAX_HEADER_WITH_AUTH +
					compound_decode_hdr_maxsz +
					decode_sequence_maxsz +
					decode_putfh_maxsz + 1) * XDR_UNIT);

स्थिर u32 nfs42_maxlistxattrs_overhead = ((RPC_MAX_HEADER_WITH_AUTH +
					compound_decode_hdr_maxsz +
					decode_sequence_maxsz +
					decode_putfh_maxsz + 3) * XDR_UNIT);

अटल व्योम encode_fallocate(काष्ठा xdr_stream *xdr,
			     स्थिर काष्ठा nfs42_falloc_args *args)
अणु
	encode_nfs4_stateid(xdr, &args->falloc_stateid);
	encode_uपूर्णांक64(xdr, args->falloc_offset);
	encode_uपूर्णांक64(xdr, args->falloc_length);
पूर्ण

अटल व्योम encode_allocate(काष्ठा xdr_stream *xdr,
			    स्थिर काष्ठा nfs42_falloc_args *args,
			    काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_ALLOCATE, decode_allocate_maxsz, hdr);
	encode_fallocate(xdr, args);
पूर्ण

अटल व्योम encode_nl4_server(काष्ठा xdr_stream *xdr,
			      स्थिर काष्ठा nl4_server *ns)
अणु
	encode_uपूर्णांक32(xdr, ns->nl4_type);
	चयन (ns->nl4_type) अणु
	हाल NL4_NAME:
	हाल NL4_URL:
		encode_string(xdr, ns->u.nl4_str_sz, ns->u.nl4_str);
		अवरोध;
	हाल NL4_NETADDR:
		encode_string(xdr, ns->u.nl4_addr.netid_len,
			      ns->u.nl4_addr.netid);
		encode_string(xdr, ns->u.nl4_addr.addr_len,
			      ns->u.nl4_addr.addr);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
	पूर्ण
पूर्ण

अटल व्योम encode_copy(काष्ठा xdr_stream *xdr,
			स्थिर काष्ठा nfs42_copy_args *args,
			काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_COPY, decode_copy_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->src_stateid);
	encode_nfs4_stateid(xdr, &args->dst_stateid);

	encode_uपूर्णांक64(xdr, args->src_pos);
	encode_uपूर्णांक64(xdr, args->dst_pos);
	encode_uपूर्णांक64(xdr, args->count);

	encode_uपूर्णांक32(xdr, 1); /* consecutive = true */
	encode_uपूर्णांक32(xdr, args->sync);
	अगर (args->cp_src == शून्य) अणु /* पूर्णांकra-ssc */
		encode_uपूर्णांक32(xdr, 0); /* no src server list */
		वापस;
	पूर्ण
	encode_uपूर्णांक32(xdr, 1); /* supporting 1 server */
	encode_nl4_server(xdr, args->cp_src);
पूर्ण

अटल व्योम encode_offload_cancel(काष्ठा xdr_stream *xdr,
				  स्थिर काष्ठा nfs42_offload_status_args *args,
				  काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_OFFLOAD_CANCEL, decode_offload_cancel_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->osa_stateid);
पूर्ण

अटल व्योम encode_copy_notअगरy(काष्ठा xdr_stream *xdr,
			       स्थिर काष्ठा nfs42_copy_notअगरy_args *args,
			       काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_COPY_NOTIFY, decode_copy_notअगरy_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->cna_src_stateid);
	encode_nl4_server(xdr, &args->cna_dst);
पूर्ण

अटल व्योम encode_deallocate(काष्ठा xdr_stream *xdr,
			      स्थिर काष्ठा nfs42_falloc_args *args,
			      काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_DEALLOCATE, decode_deallocate_maxsz, hdr);
	encode_fallocate(xdr, args);
पूर्ण

अटल व्योम encode_पढ़ो_plus(काष्ठा xdr_stream *xdr,
			     स्थिर काष्ठा nfs_pgio_args *args,
			     काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_READ_PLUS, decode_पढ़ो_plus_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->stateid);
	encode_uपूर्णांक64(xdr, args->offset);
	encode_uपूर्णांक32(xdr, args->count);
पूर्ण

अटल व्योम encode_seek(काष्ठा xdr_stream *xdr,
			स्थिर काष्ठा nfs42_seek_args *args,
			काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_SEEK, decode_seek_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->sa_stateid);
	encode_uपूर्णांक64(xdr, args->sa_offset);
	encode_uपूर्णांक32(xdr, args->sa_what);
पूर्ण

अटल व्योम encode_layoutstats(काष्ठा xdr_stream *xdr,
			       स्थिर काष्ठा nfs42_layoutstat_args *args,
			       काष्ठा nfs42_layoutstat_devinfo *devinfo,
			       काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_LAYOUTSTATS, decode_layoutstats_maxsz, hdr);
	p = reserve_space(xdr, 8 + 8);
	p = xdr_encode_hyper(p, devinfo->offset);
	p = xdr_encode_hyper(p, devinfo->length);
	encode_nfs4_stateid(xdr, &args->stateid);
	p = reserve_space(xdr, 4*8 + NFS4_DEVICEID4_SIZE + 4);
	p = xdr_encode_hyper(p, devinfo->पढ़ो_count);
	p = xdr_encode_hyper(p, devinfo->पढ़ो_bytes);
	p = xdr_encode_hyper(p, devinfo->ग_लिखो_count);
	p = xdr_encode_hyper(p, devinfo->ग_लिखो_bytes);
	p = xdr_encode_opaque_fixed(p, devinfo->dev_id.data,
			NFS4_DEVICEID4_SIZE);
	/* Encode layoutupdate4 */
	*p++ = cpu_to_be32(devinfo->layout_type);
	अगर (devinfo->ld_निजी.ops)
		devinfo->ld_निजी.ops->encode(xdr, args,
				&devinfo->ld_निजी);
	अन्यथा
		encode_uपूर्णांक32(xdr, 0);
पूर्ण

अटल व्योम encode_clone(काष्ठा xdr_stream *xdr,
			 स्थिर काष्ठा nfs42_clone_args *args,
			 काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_CLONE, decode_clone_maxsz, hdr);
	encode_nfs4_stateid(xdr, &args->src_stateid);
	encode_nfs4_stateid(xdr, &args->dst_stateid);
	p = reserve_space(xdr, 3*8);
	p = xdr_encode_hyper(p, args->src_offset);
	p = xdr_encode_hyper(p, args->dst_offset);
	xdr_encode_hyper(p, args->count);
पूर्ण

अटल व्योम encode_device_error(काष्ठा xdr_stream *xdr,
				स्थिर काष्ठा nfs42_device_error *error)
अणु
	__be32 *p;

	p = reserve_space(xdr, NFS4_DEVICEID4_SIZE + 2*4);
	p = xdr_encode_opaque_fixed(p, error->dev_id.data,
			NFS4_DEVICEID4_SIZE);
	*p++ = cpu_to_be32(error->status);
	*p = cpu_to_be32(error->opnum);
पूर्ण

अटल व्योम encode_layouterror(काष्ठा xdr_stream *xdr,
			       स्थिर काष्ठा nfs42_layout_error *args,
			       काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_LAYOUTERROR, decode_layouterror_maxsz, hdr);
	p = reserve_space(xdr, 8 + 8);
	p = xdr_encode_hyper(p, args->offset);
	p = xdr_encode_hyper(p, args->length);
	encode_nfs4_stateid(xdr, &args->stateid);
	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(1);
	encode_device_error(xdr, &args->errors[0]);
पूर्ण

अटल व्योम encode_setxattr(काष्ठा xdr_stream *xdr,
			    स्थिर काष्ठा nfs42_setxattrargs *arg,
			    काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	BUILD_BUG_ON(XATTR_CREATE != SETXATTR4_CREATE);
	BUILD_BUG_ON(XATTR_REPLACE != SETXATTR4_REPLACE);

	encode_op_hdr(xdr, OP_SETXATTR, decode_setxattr_maxsz, hdr);
	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(arg->xattr_flags);
	encode_string(xdr, म_माप(arg->xattr_name), arg->xattr_name);
	p = reserve_space(xdr, 4);
	*p = cpu_to_be32(arg->xattr_len);
	अगर (arg->xattr_len)
		xdr_ग_लिखो_pages(xdr, arg->xattr_pages, 0, arg->xattr_len);
पूर्ण

अटल पूर्णांक decode_setxattr(काष्ठा xdr_stream *xdr,
			   काष्ठा nfs4_change_info *cinfo)
अणु
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_SETXATTR);
	अगर (status)
		जाओ out;
	status = decode_change_info(xdr, cinfo);
out:
	वापस status;
पूर्ण


अटल व्योम encode_getxattr(काष्ठा xdr_stream *xdr, स्थिर अक्षर *name,
			    काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_GETXATTR, decode_getxattr_maxsz, hdr);
	encode_string(xdr, म_माप(name), name);
पूर्ण

अटल पूर्णांक decode_getxattr(काष्ठा xdr_stream *xdr,
			   काष्ठा nfs42_getxattrres *res,
			   काष्ठा rpc_rqst *req)
अणु
	पूर्णांक status;
	__be32 *p;
	u32 len, rdlen;

	status = decode_op_hdr(xdr, OP_GETXATTR);
	अगर (status)
		वापस status;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;

	len = be32_to_cpup(p);

	/*
	 * Only check against the page length here. The actual
	 * requested length may be smaller, but that is only
	 * checked against after possibly caching a valid reply.
	 */
	अगर (len > req->rq_rcv_buf.page_len)
		वापस -दुस्फल;

	res->xattr_len = len;

	अगर (len > 0) अणु
		rdlen = xdr_पढ़ो_pages(xdr, len);
		अगर (rdlen < len)
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम encode_हटाओxattr(काष्ठा xdr_stream *xdr, स्थिर अक्षर *name,
			       काष्ठा compound_hdr *hdr)
अणु
	encode_op_hdr(xdr, OP_REMOVEXATTR, decode_हटाओxattr_maxsz, hdr);
	encode_string(xdr, म_माप(name), name);
पूर्ण


अटल पूर्णांक decode_हटाओxattr(काष्ठा xdr_stream *xdr,
			   काष्ठा nfs4_change_info *cinfo)
अणु
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_REMOVEXATTR);
	अगर (status)
		जाओ out;

	status = decode_change_info(xdr, cinfo);
out:
	वापस status;
पूर्ण

अटल व्योम encode_listxattrs(काष्ठा xdr_stream *xdr,
			     स्थिर काष्ठा nfs42_listxattrsargs *arg,
			     काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_LISTXATTRS, decode_listxattrs_maxsz, hdr);

	p = reserve_space(xdr, 12);
	अगर (unlikely(!p))
		वापस;

	p = xdr_encode_hyper(p, arg->cookie);
	/*
	 * RFC 8276 says to specअगरy the full max length of the LISTXATTRS
	 * XDR reply. Count is set to the XDR length of the names array
	 * plus the खातापूर्ण marker. So, add the cookie and the names count.
	 */
	*p = cpu_to_be32(arg->count + 8 + 4);
पूर्ण

अटल पूर्णांक decode_listxattrs(काष्ठा xdr_stream *xdr,
			    काष्ठा nfs42_listxattrsres *res)
अणु
	पूर्णांक status;
	__be32 *p;
	u32 count, len, ulen;
	माप_प्रकार left, copied;
	अक्षर *buf;

	status = decode_op_hdr(xdr, OP_LISTXATTRS);
	अगर (status) अणु
		/*
		 * Special हाल: क्रम LISTXATTRS, NFS4ERR_TOOSMALL
		 * should be translated to दुस्फल.
		 */
		अगर (status == -ETOOSMALL)
			status = -दुस्फल;
		जाओ out;
	पूर्ण

	p = xdr_अंतरभूत_decode(xdr, 8);
	अगर (unlikely(!p))
		वापस -EIO;

	xdr_decode_hyper(p, &res->cookie);

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;

	left = res->xattr_len;
	buf = res->xattr_buf;

	count = be32_to_cpup(p);
	copied = 0;

	/*
	 * We have asked क्रम enough room to encode the maximum number
	 * of possible attribute names, so everything should fit.
	 *
	 * But, करोn't rely on that assumption. Just decode entries
	 * until they करोn't fit anymore, just in हाल the server did
	 * something odd.
	 */
	जबतक (count--) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (unlikely(!p))
			वापस -EIO;

		len = be32_to_cpup(p);
		अगर (len > (XATTR_NAME_MAX - XATTR_USER_PREFIX_LEN)) अणु
			status = -दुस्फल;
			जाओ out;
		पूर्ण

		p = xdr_अंतरभूत_decode(xdr, len);
		अगर (unlikely(!p))
			वापस -EIO;

		ulen = len + XATTR_USER_PREFIX_LEN + 1;
		अगर (buf) अणु
			अगर (ulen > left) अणु
				status = -दुस्फल;
				जाओ out;
			पूर्ण

			स_नकल(buf, XATTR_USER_PREFIX, XATTR_USER_PREFIX_LEN);
			स_नकल(buf + XATTR_USER_PREFIX_LEN, p, len);

			buf[ulen - 1] = 0;
			buf += ulen;
			left -= ulen;
		पूर्ण
		copied += ulen;
	पूर्ण

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;

	res->eof = be32_to_cpup(p);
	res->copied = copied;

out:
	अगर (status == -दुस्फल && res->xattr_len == XATTR_LIST_MAX)
		status = -E2BIG;

	वापस status;
पूर्ण

/*
 * Encode ALLOCATE request
 */
अटल व्योम nfs4_xdr_enc_allocate(काष्ठा rpc_rqst *req,
				  काष्ठा xdr_stream *xdr,
				  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_falloc_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->falloc_fh, &hdr);
	encode_allocate(xdr, args, &hdr);
	encode_getfattr(xdr, args->falloc_biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

अटल व्योम encode_copy_commit(काष्ठा xdr_stream *xdr,
			  स्थिर काष्ठा nfs42_copy_args *args,
			  काष्ठा compound_hdr *hdr)
अणु
	__be32 *p;

	encode_op_hdr(xdr, OP_COMMIT, decode_commit_maxsz, hdr);
	p = reserve_space(xdr, 12);
	p = xdr_encode_hyper(p, args->dst_pos);
	*p = cpu_to_be32(args->count);
पूर्ण

/*
 * Encode COPY request
 */
अटल व्योम nfs4_xdr_enc_copy(काष्ठा rpc_rqst *req,
			      काष्ठा xdr_stream *xdr,
			      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_copy_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->src_fh, &hdr);
	encode_savefh(xdr, &hdr);
	encode_putfh(xdr, args->dst_fh, &hdr);
	encode_copy(xdr, args, &hdr);
	अगर (args->sync)
		encode_copy_commit(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode OFFLOAD_CANEL request
 */
अटल व्योम nfs4_xdr_enc_offload_cancel(काष्ठा rpc_rqst *req,
					काष्ठा xdr_stream *xdr,
					स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_offload_status_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->osa_seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->osa_seq_args, &hdr);
	encode_putfh(xdr, args->osa_src_fh, &hdr);
	encode_offload_cancel(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode COPY_NOTIFY request
 */
अटल व्योम nfs4_xdr_enc_copy_notअगरy(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_copy_notअगरy_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->cna_seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->cna_seq_args, &hdr);
	encode_putfh(xdr, args->cna_src_fh, &hdr);
	encode_copy_notअगरy(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode DEALLOCATE request
 */
अटल व्योम nfs4_xdr_enc_deallocate(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_falloc_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->falloc_fh, &hdr);
	encode_deallocate(xdr, args, &hdr);
	encode_getfattr(xdr, args->falloc_biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode READ_PLUS request
 */
अटल व्योम nfs4_xdr_enc_पढ़ो_plus(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs_pgio_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_पढ़ो_plus(xdr, args, &hdr);

	rpc_prepare_reply_pages(req, args->pages, args->pgbase,
				args->count, hdr.replen);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode SEEK request
 */
अटल व्योम nfs4_xdr_enc_seek(काष्ठा rpc_rqst *req,
			      काष्ठा xdr_stream *xdr,
			      स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_seek_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->sa_fh, &hdr);
	encode_seek(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode LAYOUTSTATS request
 */
अटल व्योम nfs4_xdr_enc_layoutstats(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_layoutstat_args *args = data;
	पूर्णांक i;

	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	WARN_ON(args->num_dev > PNFS_LAYOUTSTATS_MAXDEV);
	क्रम (i = 0; i < args->num_dev; i++)
		encode_layoutstats(xdr, args, &args->devinfo[i], &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode CLONE request
 */
अटल व्योम nfs4_xdr_enc_clone(काष्ठा rpc_rqst *req,
			       काष्ठा xdr_stream *xdr,
			       स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_clone_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->src_fh, &hdr);
	encode_savefh(xdr, &hdr);
	encode_putfh(xdr, args->dst_fh, &hdr);
	encode_clone(xdr, args, &hdr);
	encode_getfattr(xdr, args->dst_biपंचांगask, &hdr);
	encode_nops(&hdr);
पूर्ण

/*
 * Encode LAYOUTERROR request
 */
अटल व्योम nfs4_xdr_enc_layouterror(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr,
				     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_layouterror_args *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;
	पूर्णांक i;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, NFS_FH(args->inode), &hdr);
	क्रम (i = 0; i < args->num_errors; i++)
		encode_layouterror(xdr, &args->errors[i], &hdr);
	encode_nops(&hdr);
पूर्ण

अटल पूर्णांक decode_allocate(काष्ठा xdr_stream *xdr, काष्ठा nfs42_falloc_res *res)
अणु
	वापस decode_op_hdr(xdr, OP_ALLOCATE);
पूर्ण

अटल पूर्णांक decode_ग_लिखो_response(काष्ठा xdr_stream *xdr,
				 काष्ठा nfs42_ग_लिखो_res *res)
अणु
	__be32 *p;
	पूर्णांक status, count;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	count = be32_to_cpup(p);
	अगर (count > 1)
		वापस -EREMOTEIO;
	अन्यथा अगर (count == 1) अणु
		status = decode_opaque_fixed(xdr, &res->stateid,
				NFS4_STATEID_SIZE);
		अगर (unlikely(status))
			वापस -EIO;
	पूर्ण
	p = xdr_अंतरभूत_decode(xdr, 8 + 4);
	अगर (unlikely(!p))
		वापस -EIO;
	p = xdr_decode_hyper(p, &res->count);
	res->verअगरier.committed = be32_to_cpup(p);
	वापस decode_verअगरier(xdr, &res->verअगरier.verअगरier);
पूर्ण

अटल पूर्णांक decode_nl4_server(काष्ठा xdr_stream *xdr, काष्ठा nl4_server *ns)
अणु
	काष्ठा nfs42_netaddr *naddr;
	uपूर्णांक32_t dummy;
	अक्षर *dummy_str;
	__be32 *p;
	पूर्णांक status;

	/* nl_type */
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;
	ns->nl4_type = be32_to_cpup(p);
	चयन (ns->nl4_type) अणु
	हाल NL4_NAME:
	हाल NL4_URL:
		status = decode_opaque_अंतरभूत(xdr, &dummy, &dummy_str);
		अगर (unlikely(status))
			वापस status;
		अगर (unlikely(dummy > NFS4_OPAQUE_LIMIT))
			वापस -EIO;
		स_नकल(&ns->u.nl4_str, dummy_str, dummy);
		ns->u.nl4_str_sz = dummy;
		अवरोध;
	हाल NL4_NETADDR:
		naddr = &ns->u.nl4_addr;

		/* netid string */
		status = decode_opaque_अंतरभूत(xdr, &dummy, &dummy_str);
		अगर (unlikely(status))
			वापस status;
		अगर (unlikely(dummy > RPCBIND_MAXNETIDLEN))
			वापस -EIO;
		naddr->netid_len = dummy;
		स_नकल(naddr->netid, dummy_str, naddr->netid_len);

		/* uaddr string */
		status = decode_opaque_अंतरभूत(xdr, &dummy, &dummy_str);
		अगर (unlikely(status))
			वापस status;
		अगर (unlikely(dummy > RPCBIND_MAXUADDRLEN))
			वापस -EIO;
		naddr->addr_len = dummy;
		स_नकल(naddr->addr, dummy_str, naddr->addr_len);
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक decode_copy_requirements(काष्ठा xdr_stream *xdr,
				    काष्ठा nfs42_copy_res *res) अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4 + 4);
	अगर (unlikely(!p))
		वापस -EIO;

	res->consecutive = be32_to_cpup(p++);
	res->synchronous = be32_to_cpup(p++);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_copy(काष्ठा xdr_stream *xdr, काष्ठा nfs42_copy_res *res)
अणु
	पूर्णांक status;

	status = decode_op_hdr(xdr, OP_COPY);
	अगर (status == NFS4ERR_OFFLOAD_NO_REQS) अणु
		status = decode_copy_requirements(xdr, res);
		अगर (status)
			वापस status;
		वापस NFS4ERR_OFFLOAD_NO_REQS;
	पूर्ण अन्यथा अगर (status)
		वापस status;

	status = decode_ग_लिखो_response(xdr, &res->ग_लिखो_res);
	अगर (status)
		वापस status;

	वापस decode_copy_requirements(xdr, res);
पूर्ण

अटल पूर्णांक decode_offload_cancel(काष्ठा xdr_stream *xdr,
				 काष्ठा nfs42_offload_status_res *res)
अणु
	वापस decode_op_hdr(xdr, OP_OFFLOAD_CANCEL);
पूर्ण

अटल पूर्णांक decode_copy_notअगरy(काष्ठा xdr_stream *xdr,
			      काष्ठा nfs42_copy_notअगरy_res *res)
अणु
	__be32 *p;
	पूर्णांक status, count;

	status = decode_op_hdr(xdr, OP_COPY_NOTIFY);
	अगर (status)
		वापस status;
	/* cnr_lease_समय */
	p = xdr_अंतरभूत_decode(xdr, 12);
	अगर (unlikely(!p))
		वापस -EIO;
	p = xdr_decode_hyper(p, &res->cnr_lease_समय.seconds);
	res->cnr_lease_समय.nseconds = be32_to_cpup(p);

	status = decode_opaque_fixed(xdr, &res->cnr_stateid, NFS4_STATEID_SIZE);
	अगर (unlikely(status))
		वापस -EIO;

	/* number of source addresses */
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		वापस -EIO;

	count = be32_to_cpup(p);
	अगर (count > 1)
		pr_warn("NFS: %s: nsvr %d > Supported. Use first servers\n",
			 __func__, count);

	status = decode_nl4_server(xdr, &res->cnr_src);
	अगर (unlikely(status))
		वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक decode_deallocate(काष्ठा xdr_stream *xdr, काष्ठा nfs42_falloc_res *res)
अणु
	वापस decode_op_hdr(xdr, OP_DEALLOCATE);
पूर्ण

अटल पूर्णांक decode_पढ़ो_plus_data(काष्ठा xdr_stream *xdr,
				 काष्ठा nfs_pgio_args *args,
				 काष्ठा nfs_pgio_res *res)
अणु
	uपूर्णांक32_t count, recvd;
	uपूर्णांक64_t offset;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 8 + 4);
	अगर (!p)
		वापस 1;

	p = xdr_decode_hyper(p, &offset);
	count = be32_to_cpup(p);
	recvd = xdr_align_data(xdr, res->count, xdr_align_size(count));
	अगर (recvd > count)
		recvd = count;
	अगर (res->count + recvd > args->count) अणु
		अगर (args->count > res->count)
			res->count += args->count - res->count;
		वापस 1;
	पूर्ण
	res->count += recvd;
	अगर (count > recvd)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक decode_पढ़ो_plus_hole(काष्ठा xdr_stream *xdr,
				 काष्ठा nfs_pgio_args *args,
				 काष्ठा nfs_pgio_res *res, uपूर्णांक32_t *eof)
अणु
	uपूर्णांक64_t offset, length, recvd;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 8 + 8);
	अगर (!p)
		वापस 1;

	p = xdr_decode_hyper(p, &offset);
	p = xdr_decode_hyper(p, &length);
	अगर (offset != args->offset + res->count) अणु
		/* Server वापसed an out-of-sequence extent */
		अगर (offset > args->offset + res->count ||
		    offset + length < args->offset + res->count) अणु
			dprपूर्णांकk("NFS: server returned out of sequence extent: "
				"offset/size = %llu/%llu != expected %llu\n",
				(अचिन्हित दीर्घ दीर्घ)offset,
				(अचिन्हित दीर्घ दीर्घ)length,
				(अचिन्हित दीर्घ दीर्घ)(args->offset +
						     res->count));
			वापस 1;
		पूर्ण
		length -= args->offset + res->count - offset;
	पूर्ण
	अगर (length + res->count > args->count) अणु
		*eof = 0;
		अगर (unlikely(res->count >= args->count))
			वापस 1;
		length = args->count - res->count;
	पूर्ण
	recvd = xdr_expand_hole(xdr, res->count, length);
	res->count += recvd;

	अगर (recvd < length)
		वापस 1;
	वापस 0;
पूर्ण

अटल पूर्णांक decode_पढ़ो_plus(काष्ठा xdr_stream *xdr, काष्ठा nfs_pgio_res *res)
अणु
	काष्ठा nfs_pgio_header *hdr =
		container_of(res, काष्ठा nfs_pgio_header, res);
	काष्ठा nfs_pgio_args *args = &hdr->args;
	uपूर्णांक32_t eof, segments, type;
	पूर्णांक status, i;
	__be32 *p;

	status = decode_op_hdr(xdr, OP_READ_PLUS);
	अगर (status)
		वापस status;

	p = xdr_अंतरभूत_decode(xdr, 4 + 4);
	अगर (unlikely(!p))
		वापस -EIO;

	res->count = 0;
	eof = be32_to_cpup(p++);
	segments = be32_to_cpup(p++);
	अगर (segments == 0)
		जाओ out;

	क्रम (i = 0; i < segments; i++) अणु
		p = xdr_अंतरभूत_decode(xdr, 4);
		अगर (!p)
			जाओ early_out;

		type = be32_to_cpup(p++);
		अगर (type == NFS4_CONTENT_DATA)
			status = decode_पढ़ो_plus_data(xdr, args, res);
		अन्यथा अगर (type == NFS4_CONTENT_HOLE)
			status = decode_पढ़ो_plus_hole(xdr, args, res, &eof);
		अन्यथा
			वापस -EINVAL;

		अगर (status < 0)
			वापस status;
		अगर (status > 0)
			जाओ early_out;
	पूर्ण

out:
	res->eof = eof;
	वापस 0;
early_out:
	अगर (unlikely(!i))
		वापस -EIO;
	res->eof = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक decode_seek(काष्ठा xdr_stream *xdr, काष्ठा nfs42_seek_res *res)
अणु
	पूर्णांक status;
	__be32 *p;

	status = decode_op_hdr(xdr, OP_SEEK);
	अगर (status)
		वापस status;

	p = xdr_अंतरभूत_decode(xdr, 4 + 8);
	अगर (unlikely(!p))
		वापस -EIO;

	res->sr_eof = be32_to_cpup(p++);
	p = xdr_decode_hyper(p, &res->sr_offset);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_layoutstats(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_LAYOUTSTATS);
पूर्ण

अटल पूर्णांक decode_clone(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_CLONE);
पूर्ण

अटल पूर्णांक decode_layouterror(काष्ठा xdr_stream *xdr)
अणु
	वापस decode_op_hdr(xdr, OP_LAYOUTERROR);
पूर्ण

/*
 * Decode ALLOCATE request
 */
अटल पूर्णांक nfs4_xdr_dec_allocate(काष्ठा rpc_rqst *rqstp,
				 काष्ठा xdr_stream *xdr,
				 व्योम *data)
अणु
	काष्ठा nfs42_falloc_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_allocate(xdr, res);
	अगर (status)
		जाओ out;
	decode_getfattr(xdr, res->falloc_fattr, res->falloc_server);
out:
	वापस status;
पूर्ण

/*
 * Decode COPY response
 */
अटल पूर्णांक nfs4_xdr_dec_copy(काष्ठा rpc_rqst *rqstp,
			     काष्ठा xdr_stream *xdr,
			     व्योम *data)
अणु
	काष्ठा nfs42_copy_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_savefh(xdr);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_copy(xdr, res);
	अगर (status)
		जाओ out;
	अगर (res->commit_res.verf)
		status = decode_commit(xdr, &res->commit_res);
out:
	वापस status;
पूर्ण

/*
 * Decode OFFLOAD_CANCEL response
 */
अटल पूर्णांक nfs4_xdr_dec_offload_cancel(काष्ठा rpc_rqst *rqstp,
				       काष्ठा xdr_stream *xdr,
				       व्योम *data)
अणु
	काष्ठा nfs42_offload_status_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->osr_seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_offload_cancel(xdr, res);

out:
	वापस status;
पूर्ण

/*
 * Decode COPY_NOTIFY response
 */
अटल पूर्णांक nfs4_xdr_dec_copy_notअगरy(काष्ठा rpc_rqst *rqstp,
				    काष्ठा xdr_stream *xdr,
				    व्योम *data)
अणु
	काष्ठा nfs42_copy_notअगरy_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->cnr_seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_copy_notअगरy(xdr, res);

out:
	वापस status;
पूर्ण

/*
 * Decode DEALLOCATE request
 */
अटल पूर्णांक nfs4_xdr_dec_deallocate(काष्ठा rpc_rqst *rqstp,
				   काष्ठा xdr_stream *xdr,
				   व्योम *data)
अणु
	काष्ठा nfs42_falloc_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_deallocate(xdr, res);
	अगर (status)
		जाओ out;
	decode_getfattr(xdr, res->falloc_fattr, res->falloc_server);
out:
	वापस status;
पूर्ण

/*
 * Decode READ_PLUS request
 */
अटल पूर्णांक nfs4_xdr_dec_पढ़ो_plus(काष्ठा rpc_rqst *rqstp,
				  काष्ठा xdr_stream *xdr,
				  व्योम *data)
अणु
	काष्ठा nfs_pgio_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_पढ़ो_plus(xdr, res);
	अगर (!status)
		status = res->count;
out:
	वापस status;
पूर्ण

/*
 * Decode SEEK request
 */
अटल पूर्णांक nfs4_xdr_dec_seek(काष्ठा rpc_rqst *rqstp,
			     काष्ठा xdr_stream *xdr,
			     व्योम *data)
अणु
	काष्ठा nfs42_seek_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_seek(xdr, res);
out:
	वापस status;
पूर्ण

/*
 * Decode LAYOUTSTATS request
 */
अटल पूर्णांक nfs4_xdr_dec_layoutstats(काष्ठा rpc_rqst *rqstp,
				    काष्ठा xdr_stream *xdr,
				    व्योम *data)
अणु
	काष्ठा nfs42_layoutstat_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status, i;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	WARN_ON(res->num_dev > PNFS_LAYOUTSTATS_MAXDEV);
	क्रम (i = 0; i < res->num_dev; i++) अणु
		status = decode_layoutstats(xdr);
		अगर (status)
			जाओ out;
	पूर्ण
out:
	res->rpc_status = status;
	वापस status;
पूर्ण

/*
 * Decode CLONE request
 */
अटल पूर्णांक nfs4_xdr_dec_clone(काष्ठा rpc_rqst *rqstp,
			      काष्ठा xdr_stream *xdr,
			      व्योम *data)
अणु
	काष्ठा nfs42_clone_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_savefh(xdr);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_clone(xdr);
	अगर (status)
		जाओ out;
	status = decode_getfattr(xdr, res->dst_fattr, res->server);

out:
	res->rpc_status = status;
	वापस status;
पूर्ण

/*
 * Decode LAYOUTERROR request
 */
अटल पूर्णांक nfs4_xdr_dec_layouterror(काष्ठा rpc_rqst *rqstp,
				    काष्ठा xdr_stream *xdr,
				    व्योम *data)
अणु
	काष्ठा nfs42_layouterror_res *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status, i;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);

	क्रम (i = 0; i < res->num_errors && status == 0; i++)
		status = decode_layouterror(xdr);
out:
	res->rpc_status = status;
	वापस status;
पूर्ण

#अगर_घोषित CONFIG_NFS_V4_2
अटल व्योम nfs4_xdr_enc_setxattr(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_setxattrargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_setxattr(xdr, args, &hdr);
	encode_nops(&hdr);
पूर्ण

अटल पूर्णांक nfs4_xdr_dec_setxattr(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				 व्योम *data)
अणु
	काष्ठा nfs42_setxattrres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, req);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;

	status = decode_setxattr(xdr, &res->cinfo);
out:
	वापस status;
पूर्ण

अटल व्योम nfs4_xdr_enc_getxattr(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_getxattrargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;
	uपूर्णांक32_t replen;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	replen = hdr.replen + op_decode_hdr_maxsz + 1;
	encode_getxattr(xdr, args->xattr_name, &hdr);

	rpc_prepare_reply_pages(req, args->xattr_pages, 0, args->xattr_len,
				replen);

	encode_nops(&hdr);
पूर्ण

अटल पूर्णांक nfs4_xdr_dec_getxattr(काष्ठा rpc_rqst *rqstp,
				 काष्ठा xdr_stream *xdr, व्योम *data)
अणु
	काष्ठा nfs42_getxattrres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_getxattr(xdr, res, rqstp);
out:
	वापस status;
पूर्ण

अटल व्योम nfs4_xdr_enc_listxattrs(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_listxattrsargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;
	uपूर्णांक32_t replen;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	replen = hdr.replen + op_decode_hdr_maxsz + 2 + 1;
	encode_listxattrs(xdr, args, &hdr);

	rpc_prepare_reply_pages(req, args->xattr_pages, 0, args->count, replen);

	encode_nops(&hdr);
पूर्ण

अटल पूर्णांक nfs4_xdr_dec_listxattrs(काष्ठा rpc_rqst *rqstp,
				   काष्ठा xdr_stream *xdr, व्योम *data)
अणु
	काष्ठा nfs42_listxattrsres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	xdr_set_scratch_page(xdr, res->scratch);

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, rqstp);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;
	status = decode_listxattrs(xdr, res);
out:
	वापस status;
पूर्ण

अटल व्योम nfs4_xdr_enc_हटाओxattr(काष्ठा rpc_rqst *req,
				     काष्ठा xdr_stream *xdr, स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfs42_हटाओxattrargs *args = data;
	काष्ठा compound_hdr hdr = अणु
		.minorversion = nfs4_xdr_minorversion(&args->seq_args),
	पूर्ण;

	encode_compound_hdr(xdr, req, &hdr);
	encode_sequence(xdr, &args->seq_args, &hdr);
	encode_putfh(xdr, args->fh, &hdr);
	encode_हटाओxattr(xdr, args->xattr_name, &hdr);
	encode_nops(&hdr);
पूर्ण

अटल पूर्णांक nfs4_xdr_dec_हटाओxattr(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr, व्योम *data)
अणु
	काष्ठा nfs42_हटाओxattrres *res = data;
	काष्ठा compound_hdr hdr;
	पूर्णांक status;

	status = decode_compound_hdr(xdr, &hdr);
	अगर (status)
		जाओ out;
	status = decode_sequence(xdr, &res->seq_res, req);
	अगर (status)
		जाओ out;
	status = decode_putfh(xdr);
	अगर (status)
		जाओ out;

	status = decode_हटाओxattr(xdr, &res->cinfo);
out:
	वापस status;
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* __LINUX_FS_NFS_NFS4_2XDR_H */
