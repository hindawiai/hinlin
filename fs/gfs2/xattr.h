<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#अगर_अघोषित __EATTR_DOT_H__
#घोषणा __EATTR_DOT_H__

काष्ठा gfs2_inode;
काष्ठा iattr;

#घोषणा GFS2_EA_REC_LEN(ea) be32_to_cpu((ea)->ea_rec_len)
#घोषणा GFS2_EA_DATA_LEN(ea) be32_to_cpu((ea)->ea_data_len)

#घोषणा GFS2_EA_SIZE(ea) \
ALIGN(माप(काष्ठा gfs2_ea_header) + (ea)->ea_name_len + \
      ((GFS2_EA_IS_STUFFED(ea)) ? GFS2_EA_DATA_LEN(ea) : \
				  (माप(__be64) * (ea)->ea_num_ptrs)), 8)

#घोषणा GFS2_EA_IS_STUFFED(ea) (!(ea)->ea_num_ptrs)
#घोषणा GFS2_EA_IS_LAST(ea) ((ea)->ea_flags & GFS2_EAFLAG_LAST)

#घोषणा GFS2_EAREQ_SIZE_STUFFED(er) \
ALIGN(माप(काष्ठा gfs2_ea_header) + (er)->er_name_len + (er)->er_data_len, 8)

#घोषणा GFS2_EA2NAME(ea) ((अक्षर *)((काष्ठा gfs2_ea_header *)(ea) + 1))
#घोषणा GFS2_EA2DATA(ea) (GFS2_EA2NAME(ea) + (ea)->ea_name_len)

#घोषणा GFS2_EA2DATAPTRS(ea) \
((__be64 *)(GFS2_EA2NAME(ea) + ALIGN((ea)->ea_name_len, 8)))

#घोषणा GFS2_EA2NEXT(ea) \
((काष्ठा gfs2_ea_header *)((अक्षर *)(ea) + GFS2_EA_REC_LEN(ea)))

#घोषणा GFS2_EA_BH2FIRST(bh) \
((काष्ठा gfs2_ea_header *)((bh)->b_data + माप(काष्ठा gfs2_meta_header)))

काष्ठा gfs2_ea_request अणु
	स्थिर अक्षर *er_name;
	अक्षर *er_data;
	अचिन्हित पूर्णांक er_name_len;
	अचिन्हित पूर्णांक er_data_len;
	अचिन्हित पूर्णांक er_type; /* GFS2_EATYPE_... */
पूर्ण;

काष्ठा gfs2_ea_location अणु
	काष्ठा buffer_head *el_bh;
	काष्ठा gfs2_ea_header *el_ea;
	काष्ठा gfs2_ea_header *el_prev;
पूर्ण;

बाह्य पूर्णांक __gfs2_xattr_set(काष्ठा inode *inode, स्थिर अक्षर *name,
			    स्थिर व्योम *value, माप_प्रकार size,
			    पूर्णांक flags, पूर्णांक type);
बाह्य sमाप_प्रकार gfs2_listxattr(काष्ठा dentry *dentry, अक्षर *buffer, माप_प्रकार size);
बाह्य पूर्णांक gfs2_ea_dealloc(काष्ठा gfs2_inode *ip);

/* Exported to acl.c */

बाह्य पूर्णांक gfs2_xattr_acl_get(काष्ठा gfs2_inode *ip, स्थिर अक्षर *name, अक्षर **data);

#पूर्ण_अगर /* __EATTR_DOT_H__ */
