<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/xattr.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/posix_acl_xattr.h>
#समावेश <linux/uaccess.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "acl.h"
#समावेश "xattr.h"
#समावेश "glock.h"
#समावेश "inode.h"
#समावेश "meta_io.h"
#समावेश "quota.h"
#समावेश "rgrp.h"
#समावेश "super.h"
#समावेश "trans.h"
#समावेश "util.h"

/*
 * ea_calc_size - वापसs the actual number of bytes the request will take up
 *                (not counting any unstuffed data blocks)
 *
 * Returns: 1 अगर the EA should be stuffed
 */

अटल पूर्णांक ea_calc_size(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक nsize, माप_प्रकार dsize,
			अचिन्हित पूर्णांक *size)
अणु
	अचिन्हित पूर्णांक jbsize = sdp->sd_jbsize;

	/* Stuffed */
	*size = ALIGN(माप(काष्ठा gfs2_ea_header) + nsize + dsize, 8);

	अगर (*size <= jbsize)
		वापस 1;

	/* Unstuffed */
	*size = ALIGN(माप(काष्ठा gfs2_ea_header) + nsize +
		      (माप(__be64) * DIV_ROUND_UP(dsize, jbsize)), 8);

	वापस 0;
पूर्ण

अटल पूर्णांक ea_check_size(काष्ठा gfs2_sbd *sdp, अचिन्हित पूर्णांक nsize, माप_प्रकार dsize)
अणु
	अचिन्हित पूर्णांक size;

	अगर (dsize > GFS2_EA_MAX_DATA_LEN)
		वापस -दुस्फल;

	ea_calc_size(sdp, nsize, dsize, &size);

	/* This can only happen with 512 byte blocks */
	अगर (size > sdp->sd_jbsize)
		वापस -दुस्फल;

	वापस 0;
पूर्ण

अटल bool gfs2_eatype_valid(काष्ठा gfs2_sbd *sdp, u8 type)
अणु
	चयन(sdp->sd_sb.sb_fs_क्रमmat) अणु
	हाल GFS2_FS_FORMAT_MAX:
		वापस true;

	हाल GFS2_FS_FORMAT_MIN:
		वापस type <= GFS2_EATYPE_SECURITY;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

प्रकार पूर्णांक (*ea_call_t) (काष्ठा gfs2_inode *ip, काष्ठा buffer_head *bh,
			  काष्ठा gfs2_ea_header *ea,
			  काष्ठा gfs2_ea_header *prev, व्योम *निजी);

अटल पूर्णांक ea_क्रमeach_i(काष्ठा gfs2_inode *ip, काष्ठा buffer_head *bh,
			ea_call_t ea_call, व्योम *data)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_ea_header *ea, *prev = शून्य;
	पूर्णांक error = 0;

	अगर (gfs2_metatype_check(GFS2_SB(&ip->i_inode), bh, GFS2_METATYPE_EA))
		वापस -EIO;

	क्रम (ea = GFS2_EA_BH2FIRST(bh);; prev = ea, ea = GFS2_EA2NEXT(ea)) अणु
		अगर (!GFS2_EA_REC_LEN(ea))
			जाओ fail;
		अगर (!(bh->b_data <= (अक्षर *)ea && (अक्षर *)GFS2_EA2NEXT(ea) <=
						  bh->b_data + bh->b_size))
			जाओ fail;
		अगर (!gfs2_eatype_valid(sdp, ea->ea_type))
			जाओ fail;
		error = ea_call(ip, bh, ea, prev, data);
		अगर (error)
			वापस error;

		अगर (GFS2_EA_IS_LAST(ea)) अणु
			अगर ((अक्षर *)GFS2_EA2NEXT(ea) !=
			    bh->b_data + bh->b_size)
				जाओ fail;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस error;

fail:
	gfs2_consist_inode(ip);
	वापस -EIO;
पूर्ण

अटल पूर्णांक ea_क्रमeach(काष्ठा gfs2_inode *ip, ea_call_t ea_call, व्योम *data)
अणु
	काष्ठा buffer_head *bh, *eabh;
	__be64 *eablk, *end;
	पूर्णांक error;

	error = gfs2_meta_पढ़ो(ip->i_gl, ip->i_eattr, DIO_WAIT, 0, &bh);
	अगर (error)
		वापस error;

	अगर (!(ip->i_diskflags & GFS2_DIF_EA_INसूचीECT)) अणु
		error = ea_क्रमeach_i(ip, bh, ea_call, data);
		जाओ out;
	पूर्ण

	अगर (gfs2_metatype_check(GFS2_SB(&ip->i_inode), bh, GFS2_METATYPE_IN)) अणु
		error = -EIO;
		जाओ out;
	पूर्ण

	eablk = (__be64 *)(bh->b_data + माप(काष्ठा gfs2_meta_header));
	end = eablk + GFS2_SB(&ip->i_inode)->sd_inptrs;

	क्रम (; eablk < end; eablk++) अणु
		u64 bn;

		अगर (!*eablk)
			अवरोध;
		bn = be64_to_cpu(*eablk);

		error = gfs2_meta_पढ़ो(ip->i_gl, bn, DIO_WAIT, 0, &eabh);
		अगर (error)
			अवरोध;
		error = ea_क्रमeach_i(ip, eabh, ea_call, data);
		brअन्यथा(eabh);
		अगर (error)
			अवरोध;
	पूर्ण
out:
	brअन्यथा(bh);
	वापस error;
पूर्ण

काष्ठा ea_find अणु
	पूर्णांक type;
	स्थिर अक्षर *name;
	माप_प्रकार namel;
	काष्ठा gfs2_ea_location *ef_el;
पूर्ण;

अटल पूर्णांक ea_find_i(काष्ठा gfs2_inode *ip, काष्ठा buffer_head *bh,
		     काष्ठा gfs2_ea_header *ea, काष्ठा gfs2_ea_header *prev,
		     व्योम *निजी)
अणु
	काष्ठा ea_find *ef = निजी;

	अगर (ea->ea_type == GFS2_EATYPE_UNUSED)
		वापस 0;

	अगर (ea->ea_type == ef->type) अणु
		अगर (ea->ea_name_len == ef->namel &&
		    !स_भेद(GFS2_EA2NAME(ea), ef->name, ea->ea_name_len)) अणु
			काष्ठा gfs2_ea_location *el = ef->ef_el;
			get_bh(bh);
			el->el_bh = bh;
			el->el_ea = ea;
			el->el_prev = prev;
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक gfs2_ea_find(काष्ठा gfs2_inode *ip, पूर्णांक type, स्थिर अक्षर *name,
			काष्ठा gfs2_ea_location *el)
अणु
	काष्ठा ea_find ef;
	पूर्णांक error;

	ef.type = type;
	ef.name = name;
	ef.namel = म_माप(name);
	ef.ef_el = el;

	स_रखो(el, 0, माप(काष्ठा gfs2_ea_location));

	error = ea_क्रमeach(ip, ea_find_i, &ef);
	अगर (error > 0)
		वापस 0;

	वापस error;
पूर्ण

/*
 * ea_dealloc_unstuffed
 *
 * Take advantage of the fact that all unstuffed blocks are
 * allocated from the same RG.  But watch, this may not always
 * be true.
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक ea_dealloc_unstuffed(काष्ठा gfs2_inode *ip, काष्ठा buffer_head *bh,
				काष्ठा gfs2_ea_header *ea,
				काष्ठा gfs2_ea_header *prev, व्योम *निजी)
अणु
	पूर्णांक *leave = निजी;
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_rgrpd *rgd;
	काष्ठा gfs2_holder rg_gh;
	__be64 *dataptrs;
	u64 bn = 0;
	u64 bstart = 0;
	अचिन्हित पूर्णांक blen = 0;
	अचिन्हित पूर्णांक blks = 0;
	अचिन्हित पूर्णांक x;
	पूर्णांक error;

	error = gfs2_rindex_update(sdp);
	अगर (error)
		वापस error;

	अगर (GFS2_EA_IS_STUFFED(ea))
		वापस 0;

	dataptrs = GFS2_EA2DATAPTRS(ea);
	क्रम (x = 0; x < ea->ea_num_ptrs; x++, dataptrs++) अणु
		अगर (*dataptrs) अणु
			blks++;
			bn = be64_to_cpu(*dataptrs);
		पूर्ण
	पूर्ण
	अगर (!blks)
		वापस 0;

	rgd = gfs2_blk2rgrpd(sdp, bn, 1);
	अगर (!rgd) अणु
		gfs2_consist_inode(ip);
		वापस -EIO;
	पूर्ण

	error = gfs2_glock_nq_init(rgd->rd_gl, LM_ST_EXCLUSIVE,
				   LM_FLAG_NODE_SCOPE, &rg_gh);
	अगर (error)
		वापस error;

	error = gfs2_trans_begin(sdp, rgd->rd_length + RES_DINODE +
				 RES_EATTR + RES_STATFS + RES_QUOTA, blks);
	अगर (error)
		जाओ out_gunlock;

	gfs2_trans_add_meta(ip->i_gl, bh);

	dataptrs = GFS2_EA2DATAPTRS(ea);
	क्रम (x = 0; x < ea->ea_num_ptrs; x++, dataptrs++) अणु
		अगर (!*dataptrs)
			अवरोध;
		bn = be64_to_cpu(*dataptrs);

		अगर (bstart + blen == bn)
			blen++;
		अन्यथा अणु
			अगर (bstart)
				gfs2_मुक्त_meta(ip, rgd, bstart, blen);
			bstart = bn;
			blen = 1;
		पूर्ण

		*dataptrs = 0;
		gfs2_add_inode_blocks(&ip->i_inode, -1);
	पूर्ण
	अगर (bstart)
		gfs2_मुक्त_meta(ip, rgd, bstart, blen);

	अगर (prev && !leave) अणु
		u32 len;

		len = GFS2_EA_REC_LEN(prev) + GFS2_EA_REC_LEN(ea);
		prev->ea_rec_len = cpu_to_be32(len);

		अगर (GFS2_EA_IS_LAST(ea))
			prev->ea_flags |= GFS2_EAFLAG_LAST;
	पूर्ण अन्यथा अणु
		ea->ea_type = GFS2_EATYPE_UNUSED;
		ea->ea_num_ptrs = 0;
	पूर्ण

	ip->i_inode.i_स_समय = current_समय(&ip->i_inode);
	__mark_inode_dirty(&ip->i_inode, I_सूचीTY_DATASYNC);

	gfs2_trans_end(sdp);

out_gunlock:
	gfs2_glock_dq_uninit(&rg_gh);
	वापस error;
पूर्ण

अटल पूर्णांक ea_हटाओ_unstuffed(काष्ठा gfs2_inode *ip, काष्ठा buffer_head *bh,
			       काष्ठा gfs2_ea_header *ea,
			       काष्ठा gfs2_ea_header *prev, पूर्णांक leave)
अणु
	पूर्णांक error;

	error = gfs2_rindex_update(GFS2_SB(&ip->i_inode));
	अगर (error)
		वापस error;

	error = gfs2_quota_hold(ip, NO_UID_QUOTA_CHANGE, NO_GID_QUOTA_CHANGE);
	अगर (error)
		जाओ out_alloc;

	error = ea_dealloc_unstuffed(ip, bh, ea, prev, (leave) ? &error : शून्य);

	gfs2_quota_unhold(ip);
out_alloc:
	वापस error;
पूर्ण

काष्ठा ea_list अणु
	काष्ठा gfs2_ea_request *ei_er;
	अचिन्हित पूर्णांक ei_size;
पूर्ण;

अटल पूर्णांक ea_list_i(काष्ठा gfs2_inode *ip, काष्ठा buffer_head *bh,
		     काष्ठा gfs2_ea_header *ea, काष्ठा gfs2_ea_header *prev,
		     व्योम *निजी)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा ea_list *ei = निजी;
	काष्ठा gfs2_ea_request *er = ei->ei_er;
	अचिन्हित पूर्णांक ea_size;
	अक्षर *prefix;
	अचिन्हित पूर्णांक l;

	अगर (ea->ea_type == GFS2_EATYPE_UNUSED)
		वापस 0;

	BUG_ON(ea->ea_type > GFS2_EATYPE_SECURITY &&
	       sdp->sd_sb.sb_fs_क्रमmat == GFS2_FS_FORMAT_MIN);
	चयन (ea->ea_type) अणु
	हाल GFS2_EATYPE_USR:
		prefix = "user.";
		l = 5;
		अवरोध;
	हाल GFS2_EATYPE_SYS:
		prefix = "system.";
		l = 7;
		अवरोध;
	हाल GFS2_EATYPE_SECURITY:
		prefix = "security.";
		l = 9;
		अवरोध;
	हाल GFS2_EATYPE_TRUSTED:
		prefix = "trusted.";
		l = 8;
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	ea_size = l + ea->ea_name_len + 1;
	अगर (er->er_data_len) अणु
		अगर (ei->ei_size + ea_size > er->er_data_len)
			वापस -दुस्फल;

		स_नकल(er->er_data + ei->ei_size, prefix, l);
		स_नकल(er->er_data + ei->ei_size + l, GFS2_EA2NAME(ea),
		       ea->ea_name_len);
		er->er_data[ei->ei_size + ea_size - 1] = 0;
	पूर्ण

	ei->ei_size += ea_size;

	वापस 0;
पूर्ण

/**
 * gfs2_listxattr - List gfs2 extended attributes
 * @dentry: The dentry whose inode we are पूर्णांकerested in
 * @buffer: The buffer to ग_लिखो the results
 * @size: The size of the buffer
 *
 * Returns: actual size of data on success, -त्रुटि_सं on error
 */

sमाप_प्रकार gfs2_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार size)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(d_inode(dentry));
	काष्ठा gfs2_ea_request er;
	काष्ठा gfs2_holder i_gh;
	पूर्णांक error;

	स_रखो(&er, 0, माप(काष्ठा gfs2_ea_request));
	अगर (size) अणु
		er.er_data = buffer;
		er.er_data_len = size;
	पूर्ण

	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY, &i_gh);
	अगर (error)
		वापस error;

	अगर (ip->i_eattr) अणु
		काष्ठा ea_list ei = अणु .ei_er = &er, .ei_size = 0 पूर्ण;

		error = ea_क्रमeach(ip, ea_list_i, &ei);
		अगर (!error)
			error = ei.ei_size;
	पूर्ण

	gfs2_glock_dq_uninit(&i_gh);

	वापस error;
पूर्ण

/**
 * gfs2_iter_unstuffed - copies the unstuffed xattr data to/from the
 *                       request buffer
 * @ip: The GFS2 inode
 * @ea: The extended attribute header काष्ठाure
 * @din: The data to be copied in
 * @करोut: The data to be copied out (one of din,करोut will be शून्य)
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_iter_unstuffed(काष्ठा gfs2_inode *ip, काष्ठा gfs2_ea_header *ea,
			       स्थिर अक्षर *din, अक्षर *करोut)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा buffer_head **bh;
	अचिन्हित पूर्णांक amount = GFS2_EA_DATA_LEN(ea);
	अचिन्हित पूर्णांक nptrs = DIV_ROUND_UP(amount, sdp->sd_jbsize);
	__be64 *dataptrs = GFS2_EA2DATAPTRS(ea);
	अचिन्हित पूर्णांक x;
	पूर्णांक error = 0;
	अचिन्हित अक्षर *pos;
	अचिन्हित cp_size;

	bh = kसुस्मृति(nptrs, माप(काष्ठा buffer_head *), GFP_NOFS);
	अगर (!bh)
		वापस -ENOMEM;

	क्रम (x = 0; x < nptrs; x++) अणु
		error = gfs2_meta_पढ़ो(ip->i_gl, be64_to_cpu(*dataptrs), 0, 0,
				       bh + x);
		अगर (error) अणु
			जबतक (x--)
				brअन्यथा(bh[x]);
			जाओ out;
		पूर्ण
		dataptrs++;
	पूर्ण

	क्रम (x = 0; x < nptrs; x++) अणु
		error = gfs2_meta_रुको(sdp, bh[x]);
		अगर (error) अणु
			क्रम (; x < nptrs; x++)
				brअन्यथा(bh[x]);
			जाओ out;
		पूर्ण
		अगर (gfs2_metatype_check(sdp, bh[x], GFS2_METATYPE_ED)) अणु
			क्रम (; x < nptrs; x++)
				brअन्यथा(bh[x]);
			error = -EIO;
			जाओ out;
		पूर्ण

		pos = bh[x]->b_data + माप(काष्ठा gfs2_meta_header);
		cp_size = (sdp->sd_jbsize > amount) ? amount : sdp->sd_jbsize;

		अगर (करोut) अणु
			स_नकल(करोut, pos, cp_size);
			करोut += sdp->sd_jbsize;
		पूर्ण

		अगर (din) अणु
			gfs2_trans_add_meta(ip->i_gl, bh[x]);
			स_नकल(pos, din, cp_size);
			din += sdp->sd_jbsize;
		पूर्ण

		amount -= sdp->sd_jbsize;
		brअन्यथा(bh[x]);
	पूर्ण

out:
	kमुक्त(bh);
	वापस error;
पूर्ण

अटल पूर्णांक gfs2_ea_get_copy(काष्ठा gfs2_inode *ip, काष्ठा gfs2_ea_location *el,
			    अक्षर *data, माप_प्रकार size)
अणु
	पूर्णांक ret;
	माप_प्रकार len = GFS2_EA_DATA_LEN(el->el_ea);
	अगर (len > size)
		वापस -दुस्फल;

	अगर (GFS2_EA_IS_STUFFED(el->el_ea)) अणु
		स_नकल(data, GFS2_EA2DATA(el->el_ea), len);
		वापस len;
	पूर्ण
	ret = gfs2_iter_unstuffed(ip, el->el_ea, शून्य, data);
	अगर (ret < 0)
		वापस ret;
	वापस len;
पूर्ण

पूर्णांक gfs2_xattr_acl_get(काष्ठा gfs2_inode *ip, स्थिर अक्षर *name, अक्षर **ppdata)
अणु
	काष्ठा gfs2_ea_location el;
	पूर्णांक error;
	पूर्णांक len;
	अक्षर *data;

	error = gfs2_ea_find(ip, GFS2_EATYPE_SYS, name, &el);
	अगर (error)
		वापस error;
	अगर (!el.el_ea)
		जाओ out;
	अगर (!GFS2_EA_DATA_LEN(el.el_ea))
		जाओ out;

	len = GFS2_EA_DATA_LEN(el.el_ea);
	data = kदो_स्मृति(len, GFP_NOFS);
	error = -ENOMEM;
	अगर (data == शून्य)
		जाओ out;

	error = gfs2_ea_get_copy(ip, &el, data, len);
	अगर (error < 0)
		kमुक्त(data);
	अन्यथा
		*ppdata = data;
out:
	brअन्यथा(el.el_bh);
	वापस error;
पूर्ण

/**
 * __gfs2_xattr_get - Get a GFS2 extended attribute
 * @inode: The inode
 * @name: The name of the extended attribute
 * @buffer: The buffer to ग_लिखो the result पूर्णांकo
 * @size: The size of the buffer
 * @type: The type of extended attribute
 *
 * Returns: actual size of data on success, -त्रुटि_सं on error
 */
अटल पूर्णांक __gfs2_xattr_get(काष्ठा inode *inode, स्थिर अक्षर *name,
			    व्योम *buffer, माप_प्रकार size, पूर्णांक type)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_ea_location el;
	पूर्णांक error;

	अगर (!ip->i_eattr)
		वापस -ENODATA;
	अगर (म_माप(name) > GFS2_EA_MAX_NAME_LEN)
		वापस -EINVAL;

	error = gfs2_ea_find(ip, type, name, &el);
	अगर (error)
		वापस error;
	अगर (!el.el_ea)
		वापस -ENODATA;
	अगर (size)
		error = gfs2_ea_get_copy(ip, &el, buffer, size);
	अन्यथा
		error = GFS2_EA_DATA_LEN(el.el_ea);
	brअन्यथा(el.el_bh);

	वापस error;
पूर्ण

अटल पूर्णांक gfs2_xattr_get(स्थिर काष्ठा xattr_handler *handler,
			  काष्ठा dentry *unused, काष्ठा inode *inode,
			  स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार size)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	पूर्णांक ret;

	/* During lookup, SELinux calls this function with the glock locked. */

	अगर (!gfs2_glock_is_locked_by_me(ip->i_gl)) अणु
		ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY, &gh);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		gfs2_holder_mark_uninitialized(&gh);
	पूर्ण
	ret = __gfs2_xattr_get(inode, name, buffer, size, handler->flags);
	अगर (gfs2_holder_initialized(&gh))
		gfs2_glock_dq_uninit(&gh);
	वापस ret;
पूर्ण

/**
 * ea_alloc_blk - allocates a new block क्रम extended attributes.
 * @ip: A poपूर्णांकer to the inode that's getting extended attributes
 * @bhp: Poपूर्णांकer to poपूर्णांकer to a काष्ठा buffer_head
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक ea_alloc_blk(काष्ठा gfs2_inode *ip, काष्ठा buffer_head **bhp)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_ea_header *ea;
	अचिन्हित पूर्णांक n = 1;
	u64 block;
	पूर्णांक error;

	error = gfs2_alloc_blocks(ip, &block, &n, 0, शून्य);
	अगर (error)
		वापस error;
	gfs2_trans_हटाओ_revoke(sdp, block, 1);
	*bhp = gfs2_meta_new(ip->i_gl, block);
	gfs2_trans_add_meta(ip->i_gl, *bhp);
	gfs2_metatype_set(*bhp, GFS2_METATYPE_EA, GFS2_FORMAT_EA);
	gfs2_buffer_clear_tail(*bhp, माप(काष्ठा gfs2_meta_header));

	ea = GFS2_EA_BH2FIRST(*bhp);
	ea->ea_rec_len = cpu_to_be32(sdp->sd_jbsize);
	ea->ea_type = GFS2_EATYPE_UNUSED;
	ea->ea_flags = GFS2_EAFLAG_LAST;
	ea->ea_num_ptrs = 0;

	gfs2_add_inode_blocks(&ip->i_inode, 1);

	वापस 0;
पूर्ण

/**
 * ea_ग_लिखो - ग_लिखोs the request info to an ea, creating new blocks अगर
 *            necessary
 * @ip: inode that is being modअगरied
 * @ea: the location of the new ea in a block
 * @er: the ग_लिखो request
 *
 * Note: करोes not update ea_rec_len or the GFS2_EAFLAG_LAST bin of ea_flags
 *
 * वापसs : त्रुटि_सं
 */

अटल पूर्णांक ea_ग_लिखो(काष्ठा gfs2_inode *ip, काष्ठा gfs2_ea_header *ea,
		    काष्ठा gfs2_ea_request *er)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	पूर्णांक error;

	ea->ea_data_len = cpu_to_be32(er->er_data_len);
	ea->ea_name_len = er->er_name_len;
	ea->ea_type = er->er_type;
	ea->__pad = 0;

	स_नकल(GFS2_EA2NAME(ea), er->er_name, er->er_name_len);

	अगर (GFS2_EAREQ_SIZE_STUFFED(er) <= sdp->sd_jbsize) अणु
		ea->ea_num_ptrs = 0;
		स_नकल(GFS2_EA2DATA(ea), er->er_data, er->er_data_len);
	पूर्ण अन्यथा अणु
		__be64 *dataptr = GFS2_EA2DATAPTRS(ea);
		स्थिर अक्षर *data = er->er_data;
		अचिन्हित पूर्णांक data_len = er->er_data_len;
		अचिन्हित पूर्णांक copy;
		अचिन्हित पूर्णांक x;

		ea->ea_num_ptrs = DIV_ROUND_UP(er->er_data_len, sdp->sd_jbsize);
		क्रम (x = 0; x < ea->ea_num_ptrs; x++) अणु
			काष्ठा buffer_head *bh;
			u64 block;
			पूर्णांक mh_size = माप(काष्ठा gfs2_meta_header);
			अचिन्हित पूर्णांक n = 1;

			error = gfs2_alloc_blocks(ip, &block, &n, 0, शून्य);
			अगर (error)
				वापस error;
			gfs2_trans_हटाओ_revoke(sdp, block, 1);
			bh = gfs2_meta_new(ip->i_gl, block);
			gfs2_trans_add_meta(ip->i_gl, bh);
			gfs2_metatype_set(bh, GFS2_METATYPE_ED, GFS2_FORMAT_ED);

			gfs2_add_inode_blocks(&ip->i_inode, 1);

			copy = data_len > sdp->sd_jbsize ? sdp->sd_jbsize :
							   data_len;
			स_नकल(bh->b_data + mh_size, data, copy);
			अगर (copy < sdp->sd_jbsize)
				स_रखो(bh->b_data + mh_size + copy, 0,
				       sdp->sd_jbsize - copy);

			*dataptr++ = cpu_to_be64(bh->b_blocknr);
			data += copy;
			data_len -= copy;

			brअन्यथा(bh);
		पूर्ण

		gfs2_निश्चित_withdraw(sdp, !data_len);
	पूर्ण

	वापस 0;
पूर्ण

प्रकार पूर्णांक (*ea_skeleton_call_t) (काष्ठा gfs2_inode *ip,
				   काष्ठा gfs2_ea_request *er, व्योम *निजी);

अटल पूर्णांक ea_alloc_skeleton(काष्ठा gfs2_inode *ip, काष्ठा gfs2_ea_request *er,
			     अचिन्हित पूर्णांक blks,
			     ea_skeleton_call_t skeleton_call, व्योम *निजी)
अणु
	काष्ठा gfs2_alloc_parms ap = अणु .target = blks पूर्ण;
	पूर्णांक error;

	error = gfs2_rindex_update(GFS2_SB(&ip->i_inode));
	अगर (error)
		वापस error;

	error = gfs2_quota_lock_check(ip, &ap);
	अगर (error)
		वापस error;

	error = gfs2_inplace_reserve(ip, &ap);
	अगर (error)
		जाओ out_gunlock_q;

	error = gfs2_trans_begin(GFS2_SB(&ip->i_inode),
				 blks + gfs2_rg_blocks(ip, blks) +
				 RES_DINODE + RES_STATFS + RES_QUOTA, 0);
	अगर (error)
		जाओ out_ipres;

	error = skeleton_call(ip, er, निजी);
	अगर (error)
		जाओ out_end_trans;

	ip->i_inode.i_स_समय = current_समय(&ip->i_inode);
	__mark_inode_dirty(&ip->i_inode, I_सूचीTY_DATASYNC);

out_end_trans:
	gfs2_trans_end(GFS2_SB(&ip->i_inode));
out_ipres:
	gfs2_inplace_release(ip);
out_gunlock_q:
	gfs2_quota_unlock(ip);
	वापस error;
पूर्ण

अटल पूर्णांक ea_init_i(काष्ठा gfs2_inode *ip, काष्ठा gfs2_ea_request *er,
		     व्योम *निजी)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक error;

	error = ea_alloc_blk(ip, &bh);
	अगर (error)
		वापस error;

	ip->i_eattr = bh->b_blocknr;
	error = ea_ग_लिखो(ip, GFS2_EA_BH2FIRST(bh), er);

	brअन्यथा(bh);

	वापस error;
पूर्ण

/*
 * ea_init - initializes a new eattr block
 *
 * Returns: त्रुटि_सं
 */
अटल पूर्णांक ea_init(काष्ठा gfs2_inode *ip, पूर्णांक type, स्थिर अक्षर *name,
		   स्थिर व्योम *data, माप_प्रकार size)
अणु
	काष्ठा gfs2_ea_request er;
	अचिन्हित पूर्णांक jbsize = GFS2_SB(&ip->i_inode)->sd_jbsize;
	अचिन्हित पूर्णांक blks = 1;

	er.er_type = type;
	er.er_name = name;
	er.er_name_len = म_माप(name);
	er.er_data = (व्योम *)data;
	er.er_data_len = size;

	अगर (GFS2_EAREQ_SIZE_STUFFED(&er) > jbsize)
		blks += DIV_ROUND_UP(er.er_data_len, jbsize);

	वापस ea_alloc_skeleton(ip, &er, blks, ea_init_i, शून्य);
पूर्ण

अटल काष्ठा gfs2_ea_header *ea_split_ea(काष्ठा gfs2_ea_header *ea)
अणु
	u32 ea_size = GFS2_EA_SIZE(ea);
	काष्ठा gfs2_ea_header *new = (काष्ठा gfs2_ea_header *)((अक्षर *)ea +
				     ea_size);
	u32 new_size = GFS2_EA_REC_LEN(ea) - ea_size;
	पूर्णांक last = ea->ea_flags & GFS2_EAFLAG_LAST;

	ea->ea_rec_len = cpu_to_be32(ea_size);
	ea->ea_flags ^= last;

	new->ea_rec_len = cpu_to_be32(new_size);
	new->ea_flags = last;

	वापस new;
पूर्ण

अटल व्योम ea_set_हटाओ_stuffed(काष्ठा gfs2_inode *ip,
				  काष्ठा gfs2_ea_location *el)
अणु
	काष्ठा gfs2_ea_header *ea = el->el_ea;
	काष्ठा gfs2_ea_header *prev = el->el_prev;
	u32 len;

	gfs2_trans_add_meta(ip->i_gl, el->el_bh);

	अगर (!prev || !GFS2_EA_IS_STUFFED(ea)) अणु
		ea->ea_type = GFS2_EATYPE_UNUSED;
		वापस;
	पूर्ण अन्यथा अगर (GFS2_EA2NEXT(prev) != ea) अणु
		prev = GFS2_EA2NEXT(prev);
		gfs2_निश्चित_withdraw(GFS2_SB(&ip->i_inode), GFS2_EA2NEXT(prev) == ea);
	पूर्ण

	len = GFS2_EA_REC_LEN(prev) + GFS2_EA_REC_LEN(ea);
	prev->ea_rec_len = cpu_to_be32(len);

	अगर (GFS2_EA_IS_LAST(ea))
		prev->ea_flags |= GFS2_EAFLAG_LAST;
पूर्ण

काष्ठा ea_set अणु
	पूर्णांक ea_split;

	काष्ठा gfs2_ea_request *es_er;
	काष्ठा gfs2_ea_location *es_el;

	काष्ठा buffer_head *es_bh;
	काष्ठा gfs2_ea_header *es_ea;
पूर्ण;

अटल पूर्णांक ea_set_simple_noalloc(काष्ठा gfs2_inode *ip, काष्ठा buffer_head *bh,
				 काष्ठा gfs2_ea_header *ea, काष्ठा ea_set *es)
अणु
	काष्ठा gfs2_ea_request *er = es->es_er;
	पूर्णांक error;

	error = gfs2_trans_begin(GFS2_SB(&ip->i_inode), RES_DINODE + 2 * RES_EATTR, 0);
	अगर (error)
		वापस error;

	gfs2_trans_add_meta(ip->i_gl, bh);

	अगर (es->ea_split)
		ea = ea_split_ea(ea);

	ea_ग_लिखो(ip, ea, er);

	अगर (es->es_el)
		ea_set_हटाओ_stuffed(ip, es->es_el);

	ip->i_inode.i_स_समय = current_समय(&ip->i_inode);
	__mark_inode_dirty(&ip->i_inode, I_सूचीTY_DATASYNC);

	gfs2_trans_end(GFS2_SB(&ip->i_inode));
	वापस error;
पूर्ण

अटल पूर्णांक ea_set_simple_alloc(काष्ठा gfs2_inode *ip,
			       काष्ठा gfs2_ea_request *er, व्योम *निजी)
अणु
	काष्ठा ea_set *es = निजी;
	काष्ठा gfs2_ea_header *ea = es->es_ea;
	पूर्णांक error;

	gfs2_trans_add_meta(ip->i_gl, es->es_bh);

	अगर (es->ea_split)
		ea = ea_split_ea(ea);

	error = ea_ग_लिखो(ip, ea, er);
	अगर (error)
		वापस error;

	अगर (es->es_el)
		ea_set_हटाओ_stuffed(ip, es->es_el);

	वापस 0;
पूर्ण

अटल पूर्णांक ea_set_simple(काष्ठा gfs2_inode *ip, काष्ठा buffer_head *bh,
			 काष्ठा gfs2_ea_header *ea, काष्ठा gfs2_ea_header *prev,
			 व्योम *निजी)
अणु
	काष्ठा ea_set *es = निजी;
	अचिन्हित पूर्णांक size;
	पूर्णांक stuffed;
	पूर्णांक error;

	stuffed = ea_calc_size(GFS2_SB(&ip->i_inode), es->es_er->er_name_len,
			       es->es_er->er_data_len, &size);

	अगर (ea->ea_type == GFS2_EATYPE_UNUSED) अणु
		अगर (GFS2_EA_REC_LEN(ea) < size)
			वापस 0;
		अगर (!GFS2_EA_IS_STUFFED(ea)) अणु
			error = ea_हटाओ_unstuffed(ip, bh, ea, prev, 1);
			अगर (error)
				वापस error;
		पूर्ण
		es->ea_split = 0;
	पूर्ण अन्यथा अगर (GFS2_EA_REC_LEN(ea) - GFS2_EA_SIZE(ea) >= size)
		es->ea_split = 1;
	अन्यथा
		वापस 0;

	अगर (stuffed) अणु
		error = ea_set_simple_noalloc(ip, bh, ea, es);
		अगर (error)
			वापस error;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक blks;

		es->es_bh = bh;
		es->es_ea = ea;
		blks = 2 + DIV_ROUND_UP(es->es_er->er_data_len,
					GFS2_SB(&ip->i_inode)->sd_jbsize);

		error = ea_alloc_skeleton(ip, es->es_er, blks,
					  ea_set_simple_alloc, es);
		अगर (error)
			वापस error;
	पूर्ण

	वापस 1;
पूर्ण

अटल पूर्णांक ea_set_block(काष्ठा gfs2_inode *ip, काष्ठा gfs2_ea_request *er,
			व्योम *निजी)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा buffer_head *indbh, *newbh;
	__be64 *eablk;
	पूर्णांक error;
	पूर्णांक mh_size = माप(काष्ठा gfs2_meta_header);

	अगर (ip->i_diskflags & GFS2_DIF_EA_INसूचीECT) अणु
		__be64 *end;

		error = gfs2_meta_पढ़ो(ip->i_gl, ip->i_eattr, DIO_WAIT, 0,
				       &indbh);
		अगर (error)
			वापस error;

		अगर (gfs2_metatype_check(sdp, indbh, GFS2_METATYPE_IN)) अणु
			error = -EIO;
			जाओ out;
		पूर्ण

		eablk = (__be64 *)(indbh->b_data + mh_size);
		end = eablk + sdp->sd_inptrs;

		क्रम (; eablk < end; eablk++)
			अगर (!*eablk)
				अवरोध;

		अगर (eablk == end) अणु
			error = -ENOSPC;
			जाओ out;
		पूर्ण

		gfs2_trans_add_meta(ip->i_gl, indbh);
	पूर्ण अन्यथा अणु
		u64 blk;
		अचिन्हित पूर्णांक n = 1;
		error = gfs2_alloc_blocks(ip, &blk, &n, 0, शून्य);
		अगर (error)
			वापस error;
		gfs2_trans_हटाओ_revoke(sdp, blk, 1);
		indbh = gfs2_meta_new(ip->i_gl, blk);
		gfs2_trans_add_meta(ip->i_gl, indbh);
		gfs2_metatype_set(indbh, GFS2_METATYPE_IN, GFS2_FORMAT_IN);
		gfs2_buffer_clear_tail(indbh, mh_size);

		eablk = (__be64 *)(indbh->b_data + mh_size);
		*eablk = cpu_to_be64(ip->i_eattr);
		ip->i_eattr = blk;
		ip->i_diskflags |= GFS2_DIF_EA_INसूचीECT;
		gfs2_add_inode_blocks(&ip->i_inode, 1);

		eablk++;
	पूर्ण

	error = ea_alloc_blk(ip, &newbh);
	अगर (error)
		जाओ out;

	*eablk = cpu_to_be64((u64)newbh->b_blocknr);
	error = ea_ग_लिखो(ip, GFS2_EA_BH2FIRST(newbh), er);
	brअन्यथा(newbh);
	अगर (error)
		जाओ out;

	अगर (निजी)
		ea_set_हटाओ_stuffed(ip, निजी);

out:
	brअन्यथा(indbh);
	वापस error;
पूर्ण

अटल पूर्णांक ea_set_i(काष्ठा gfs2_inode *ip, पूर्णांक type, स्थिर अक्षर *name,
		    स्थिर व्योम *value, माप_प्रकार size, काष्ठा gfs2_ea_location *el)
अणु
	काष्ठा gfs2_ea_request er;
	काष्ठा ea_set es;
	अचिन्हित पूर्णांक blks = 2;
	पूर्णांक error;

	er.er_type = type;
	er.er_name = name;
	er.er_data = (व्योम *)value;
	er.er_name_len = म_माप(name);
	er.er_data_len = size;

	स_रखो(&es, 0, माप(काष्ठा ea_set));
	es.es_er = &er;
	es.es_el = el;

	error = ea_क्रमeach(ip, ea_set_simple, &es);
	अगर (error > 0)
		वापस 0;
	अगर (error)
		वापस error;

	अगर (!(ip->i_diskflags & GFS2_DIF_EA_INसूचीECT))
		blks++;
	अगर (GFS2_EAREQ_SIZE_STUFFED(&er) > GFS2_SB(&ip->i_inode)->sd_jbsize)
		blks += DIV_ROUND_UP(er.er_data_len, GFS2_SB(&ip->i_inode)->sd_jbsize);

	वापस ea_alloc_skeleton(ip, &er, blks, ea_set_block, el);
पूर्ण

अटल पूर्णांक ea_set_हटाओ_unstuffed(काष्ठा gfs2_inode *ip,
				   काष्ठा gfs2_ea_location *el)
अणु
	अगर (el->el_prev && GFS2_EA2NEXT(el->el_prev) != el->el_ea) अणु
		el->el_prev = GFS2_EA2NEXT(el->el_prev);
		gfs2_निश्चित_withdraw(GFS2_SB(&ip->i_inode),
				     GFS2_EA2NEXT(el->el_prev) == el->el_ea);
	पूर्ण

	वापस ea_हटाओ_unstuffed(ip, el->el_bh, el->el_ea, el->el_prev, 0);
पूर्ण

अटल पूर्णांक ea_हटाओ_stuffed(काष्ठा gfs2_inode *ip, काष्ठा gfs2_ea_location *el)
अणु
	काष्ठा gfs2_ea_header *ea = el->el_ea;
	काष्ठा gfs2_ea_header *prev = el->el_prev;
	पूर्णांक error;

	error = gfs2_trans_begin(GFS2_SB(&ip->i_inode), RES_DINODE + RES_EATTR, 0);
	अगर (error)
		वापस error;

	gfs2_trans_add_meta(ip->i_gl, el->el_bh);

	अगर (prev) अणु
		u32 len;

		len = GFS2_EA_REC_LEN(prev) + GFS2_EA_REC_LEN(ea);
		prev->ea_rec_len = cpu_to_be32(len);

		अगर (GFS2_EA_IS_LAST(ea))
			prev->ea_flags |= GFS2_EAFLAG_LAST;
	पूर्ण अन्यथा अणु
		ea->ea_type = GFS2_EATYPE_UNUSED;
	पूर्ण

	ip->i_inode.i_स_समय = current_समय(&ip->i_inode);
	__mark_inode_dirty(&ip->i_inode, I_सूचीTY_DATASYNC);

	gfs2_trans_end(GFS2_SB(&ip->i_inode));

	वापस error;
पूर्ण

/**
 * gfs2_xattr_हटाओ - Remove a GFS2 extended attribute
 * @ip: The inode
 * @type: The type of the extended attribute
 * @name: The name of the extended attribute
 *
 * This is not called directly by the VFS since we use the (common)
 * scheme of making a "set with NULL data" mean a हटाओ request. Note
 * that this is dअगरferent from a set with zero length data.
 *
 * Returns: 0, or त्रुटि_सं on failure
 */

अटल पूर्णांक gfs2_xattr_हटाओ(काष्ठा gfs2_inode *ip, पूर्णांक type, स्थिर अक्षर *name)
अणु
	काष्ठा gfs2_ea_location el;
	पूर्णांक error;

	अगर (!ip->i_eattr)
		वापस -ENODATA;

	error = gfs2_ea_find(ip, type, name, &el);
	अगर (error)
		वापस error;
	अगर (!el.el_ea)
		वापस -ENODATA;

	अगर (GFS2_EA_IS_STUFFED(el.el_ea))
		error = ea_हटाओ_stuffed(ip, &el);
	अन्यथा
		error = ea_हटाओ_unstuffed(ip, el.el_bh, el.el_ea, el.el_prev, 0);

	brअन्यथा(el.el_bh);

	वापस error;
पूर्ण

/**
 * __gfs2_xattr_set - Set (or हटाओ) a GFS2 extended attribute
 * @inode: The inode
 * @name: The name of the extended attribute
 * @value: The value of the extended attribute (शून्य क्रम हटाओ)
 * @size: The size of the @value argument
 * @flags: Create or Replace
 * @type: The type of the extended attribute
 *
 * See gfs2_xattr_हटाओ() क्रम details of the removal of xattrs.
 *
 * Returns: 0 or त्रुटि_सं on failure
 */

पूर्णांक __gfs2_xattr_set(काष्ठा inode *inode, स्थिर अक्षर *name,
		   स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags, पूर्णांक type)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा gfs2_ea_location el;
	अचिन्हित पूर्णांक namel = म_माप(name);
	पूर्णांक error;

	अगर (IS_IMMUTABLE(inode) || IS_APPEND(inode))
		वापस -EPERM;
	अगर (namel > GFS2_EA_MAX_NAME_LEN)
		वापस -दुस्फल;

	अगर (value == शून्य) अणु
		error = gfs2_xattr_हटाओ(ip, type, name);
		अगर (error == -ENODATA && !(flags & XATTR_REPLACE))
			error = 0;
		वापस error;
	पूर्ण

	अगर (ea_check_size(sdp, namel, size))
		वापस -दुस्फल;

	अगर (!ip->i_eattr) अणु
		अगर (flags & XATTR_REPLACE)
			वापस -ENODATA;
		वापस ea_init(ip, type, name, value, size);
	पूर्ण

	error = gfs2_ea_find(ip, type, name, &el);
	अगर (error)
		वापस error;

	अगर (el.el_ea) अणु
		अगर (ip->i_diskflags & GFS2_DIF_APPENDONLY) अणु
			brअन्यथा(el.el_bh);
			वापस -EPERM;
		पूर्ण

		error = -EEXIST;
		अगर (!(flags & XATTR_CREATE)) अणु
			पूर्णांक unstuffed = !GFS2_EA_IS_STUFFED(el.el_ea);
			error = ea_set_i(ip, type, name, value, size, &el);
			अगर (!error && unstuffed)
				ea_set_हटाओ_unstuffed(ip, &el);
		पूर्ण

		brअन्यथा(el.el_bh);
		वापस error;
	पूर्ण

	error = -ENODATA;
	अगर (!(flags & XATTR_REPLACE))
		error = ea_set_i(ip, type, name, value, size, शून्य);

	वापस error;
पूर्ण

अटल पूर्णांक gfs2_xattr_set(स्थिर काष्ठा xattr_handler *handler,
			  काष्ठा user_namespace *mnt_userns,
			  काष्ठा dentry *unused, काष्ठा inode *inode,
			  स्थिर अक्षर *name, स्थिर व्योम *value,
			  माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	पूर्णांक ret;

	ret = gfs2_qa_get(ip);
	अगर (ret)
		वापस ret;

	/* May be called from gfs_setattr with the glock locked. */

	अगर (!gfs2_glock_is_locked_by_me(ip->i_gl)) अणु
		ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &gh);
		अगर (ret)
			जाओ out;
	पूर्ण अन्यथा अणु
		अगर (WARN_ON_ONCE(ip->i_gl->gl_state != LM_ST_EXCLUSIVE)) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण
		gfs2_holder_mark_uninitialized(&gh);
	पूर्ण
	ret = __gfs2_xattr_set(inode, name, value, size, flags, handler->flags);
	अगर (gfs2_holder_initialized(&gh))
		gfs2_glock_dq_uninit(&gh);
out:
	gfs2_qa_put(ip);
	वापस ret;
पूर्ण

अटल पूर्णांक ea_dealloc_indirect(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_rgrp_list rlist;
	काष्ठा gfs2_rgrpd *rgd;
	काष्ठा buffer_head *indbh, *dibh;
	__be64 *eablk, *end;
	अचिन्हित पूर्णांक rg_blocks = 0;
	u64 bstart = 0;
	अचिन्हित पूर्णांक blen = 0;
	अचिन्हित पूर्णांक blks = 0;
	अचिन्हित पूर्णांक x;
	पूर्णांक error;

	error = gfs2_rindex_update(sdp);
	अगर (error)
		वापस error;

	स_रखो(&rlist, 0, माप(काष्ठा gfs2_rgrp_list));

	error = gfs2_meta_पढ़ो(ip->i_gl, ip->i_eattr, DIO_WAIT, 0, &indbh);
	अगर (error)
		वापस error;

	अगर (gfs2_metatype_check(sdp, indbh, GFS2_METATYPE_IN)) अणु
		error = -EIO;
		जाओ out;
	पूर्ण

	eablk = (__be64 *)(indbh->b_data + माप(काष्ठा gfs2_meta_header));
	end = eablk + sdp->sd_inptrs;

	क्रम (; eablk < end; eablk++) अणु
		u64 bn;

		अगर (!*eablk)
			अवरोध;
		bn = be64_to_cpu(*eablk);

		अगर (bstart + blen == bn)
			blen++;
		अन्यथा अणु
			अगर (bstart)
				gfs2_rlist_add(ip, &rlist, bstart);
			bstart = bn;
			blen = 1;
		पूर्ण
		blks++;
	पूर्ण
	अगर (bstart)
		gfs2_rlist_add(ip, &rlist, bstart);
	अन्यथा
		जाओ out;

	gfs2_rlist_alloc(&rlist);

	क्रम (x = 0; x < rlist.rl_rgrps; x++) अणु
		rgd = gfs2_glock2rgrp(rlist.rl_ghs[x].gh_gl);
		rg_blocks += rgd->rd_length;
	पूर्ण

	error = gfs2_glock_nq_m(rlist.rl_rgrps, rlist.rl_ghs);
	अगर (error)
		जाओ out_rlist_मुक्त;

	error = gfs2_trans_begin(sdp, rg_blocks + RES_DINODE + RES_INसूचीECT +
				 RES_STATFS + RES_QUOTA, blks);
	अगर (error)
		जाओ out_gunlock;

	gfs2_trans_add_meta(ip->i_gl, indbh);

	eablk = (__be64 *)(indbh->b_data + माप(काष्ठा gfs2_meta_header));
	bstart = 0;
	rgd = शून्य;
	blen = 0;

	क्रम (; eablk < end; eablk++) अणु
		u64 bn;

		अगर (!*eablk)
			अवरोध;
		bn = be64_to_cpu(*eablk);

		अगर (bstart + blen == bn)
			blen++;
		अन्यथा अणु
			अगर (bstart)
				gfs2_मुक्त_meta(ip, rgd, bstart, blen);
			bstart = bn;
			rgd = gfs2_blk2rgrpd(sdp, bstart, true);
			blen = 1;
		पूर्ण

		*eablk = 0;
		gfs2_add_inode_blocks(&ip->i_inode, -1);
	पूर्ण
	अगर (bstart)
		gfs2_मुक्त_meta(ip, rgd, bstart, blen);

	ip->i_diskflags &= ~GFS2_DIF_EA_INसूचीECT;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (!error) अणु
		gfs2_trans_add_meta(ip->i_gl, dibh);
		gfs2_dinode_out(ip, dibh->b_data);
		brअन्यथा(dibh);
	पूर्ण

	gfs2_trans_end(sdp);

out_gunlock:
	gfs2_glock_dq_m(rlist.rl_rgrps, rlist.rl_ghs);
out_rlist_मुक्त:
	gfs2_rlist_मुक्त(&rlist);
out:
	brअन्यथा(indbh);
	वापस error;
पूर्ण

अटल पूर्णांक ea_dealloc_block(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_rgrpd *rgd;
	काष्ठा buffer_head *dibh;
	काष्ठा gfs2_holder gh;
	पूर्णांक error;

	error = gfs2_rindex_update(sdp);
	अगर (error)
		वापस error;

	rgd = gfs2_blk2rgrpd(sdp, ip->i_eattr, 1);
	अगर (!rgd) अणु
		gfs2_consist_inode(ip);
		वापस -EIO;
	पूर्ण

	error = gfs2_glock_nq_init(rgd->rd_gl, LM_ST_EXCLUSIVE,
				   LM_FLAG_NODE_SCOPE, &gh);
	अगर (error)
		वापस error;

	error = gfs2_trans_begin(sdp, RES_RG_BIT + RES_DINODE + RES_STATFS +
				 RES_QUOTA, 1);
	अगर (error)
		जाओ out_gunlock;

	gfs2_मुक्त_meta(ip, rgd, ip->i_eattr, 1);

	ip->i_eattr = 0;
	gfs2_add_inode_blocks(&ip->i_inode, -1);

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (!error) अणु
		gfs2_trans_add_meta(ip->i_gl, dibh);
		gfs2_dinode_out(ip, dibh->b_data);
		brअन्यथा(dibh);
	पूर्ण

	gfs2_trans_end(sdp);

out_gunlock:
	gfs2_glock_dq_uninit(&gh);
	वापस error;
पूर्ण

/**
 * gfs2_ea_dealloc - deallocate the extended attribute विभाजन
 * @ip: the inode
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_ea_dealloc(काष्ठा gfs2_inode *ip)
अणु
	पूर्णांक error;

	error = gfs2_rindex_update(GFS2_SB(&ip->i_inode));
	अगर (error)
		वापस error;

	error = gfs2_quota_hold(ip, NO_UID_QUOTA_CHANGE, NO_GID_QUOTA_CHANGE);
	अगर (error)
		वापस error;

	error = ea_क्रमeach(ip, ea_dealloc_unstuffed, शून्य);
	अगर (error)
		जाओ out_quota;

	अगर (ip->i_diskflags & GFS2_DIF_EA_INसूचीECT) अणु
		error = ea_dealloc_indirect(ip);
		अगर (error)
			जाओ out_quota;
	पूर्ण

	error = ea_dealloc_block(ip);

out_quota:
	gfs2_quota_unhold(ip);
	वापस error;
पूर्ण

अटल स्थिर काष्ठा xattr_handler gfs2_xattr_user_handler = अणु
	.prefix = XATTR_USER_PREFIX,
	.flags  = GFS2_EATYPE_USR,
	.get    = gfs2_xattr_get,
	.set    = gfs2_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler gfs2_xattr_security_handler = अणु
	.prefix = XATTR_SECURITY_PREFIX,
	.flags  = GFS2_EATYPE_SECURITY,
	.get    = gfs2_xattr_get,
	.set    = gfs2_xattr_set,
पूर्ण;

अटल bool
gfs2_xattr_trusted_list(काष्ठा dentry *dentry)
अणु
	वापस capable(CAP_SYS_ADMIN);
पूर्ण

अटल स्थिर काष्ठा xattr_handler gfs2_xattr_trusted_handler = अणु
	.prefix = XATTR_TRUSTED_PREFIX,
	.flags  = GFS2_EATYPE_TRUSTED,
	.list	= gfs2_xattr_trusted_list,
	.get    = gfs2_xattr_get,
	.set    = gfs2_xattr_set,
पूर्ण;

स्थिर काष्ठा xattr_handler *gfs2_xattr_handlers_max[] = अणु
	/* GFS2_FS_FORMAT_MAX */
	&gfs2_xattr_trusted_handler,

	/* GFS2_FS_FORMAT_MIN */
	&gfs2_xattr_user_handler,
	&gfs2_xattr_security_handler,
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
	शून्य,
पूर्ण;

स्थिर काष्ठा xattr_handler **gfs2_xattr_handlers_min = gfs2_xattr_handlers_max + 1;
