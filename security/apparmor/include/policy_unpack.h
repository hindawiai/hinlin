<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor policy loading पूर्णांकerface function definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#अगर_अघोषित __POLICY_INTERFACE_H
#घोषणा __POLICY_INTERFACE_H

#समावेश <linux/list.h>
#समावेश <linux/kref.h>
#समावेश <linux/dcache.h>
#समावेश <linux/workqueue.h>

काष्ठा aa_load_ent अणु
	काष्ठा list_head list;
	काष्ठा aa_profile *new;
	काष्ठा aa_profile *old;
	काष्ठा aa_profile *नाम;
	स्थिर अक्षर *ns_name;
पूर्ण;

व्योम aa_load_ent_मुक्त(काष्ठा aa_load_ent *ent);
काष्ठा aa_load_ent *aa_load_ent_alloc(व्योम);

#घोषणा PACKED_FLAG_HAT		1

#घोषणा PACKED_MODE_ENFORCE	0
#घोषणा PACKED_MODE_COMPLAIN	1
#घोषणा PACKED_MODE_KILL	2
#घोषणा PACKED_MODE_UNCONFINED	3

काष्ठा aa_ns;

क्रमागत अणु
	AAFS_LOADDATA_ABI = 0,
	AAFS_LOADDATA_REVISION,
	AAFS_LOADDATA_HASH,
	AAFS_LOADDATA_DATA,
	AAFS_LOADDATA_COMPRESSED_SIZE,
	AAFS_LOADDATA_सूची,		/* must be last actual entry */
	AAFS_LOADDATA_NDENTS		/* count of entries */
पूर्ण;

/*
 * काष्ठा aa_loaddata - buffer of policy raw_data set
 *
 * there is no loaddata ref क्रम being on ns list, nor a ref from
 * d_inode(@dentry) when grab a ref from these, @ns->lock must be held
 * && __aa_get_loaddata() needs to be used, and the वापस value
 * checked, अगर शून्य the loaddata is alपढ़ोy being reaped and should be
 * considered dead.
 */
काष्ठा aa_loaddata अणु
	काष्ठा kref count;
	काष्ठा list_head list;
	काष्ठा work_काष्ठा work;
	काष्ठा dentry *dents[AAFS_LOADDATA_NDENTS];
	काष्ठा aa_ns *ns;
	अक्षर *name;
	माप_प्रकार size;			/* the original size of the payload */
	माप_प्रकार compressed_size;		/* the compressed size of the payload */
	दीर्घ revision;			/* the ns policy revision this caused */
	पूर्णांक abi;
	अचिन्हित अक्षर *hash;

	/* Poपूर्णांकer to payload. If @compressed_size > 0, then this is the
	 * compressed version of the payload, अन्यथा it is the uncompressed
	 * version (with the size indicated by @size).
	 */
	अक्षर *data;
पूर्ण;

पूर्णांक aa_unpack(काष्ठा aa_loaddata *udata, काष्ठा list_head *lh, स्थिर अक्षर **ns);

/**
 * __aa_get_loaddata - get a reference count to uncounted data reference
 * @data: reference to get a count on
 *
 * Returns: poपूर्णांकer to reference OR शून्य अगर race is lost and reference is
 *          being repeated.
 * Requires: @data->ns->lock held, and the वापस code MUST be checked
 *
 * Use only from inode->i_निजी and @data->list found references
 */
अटल अंतरभूत काष्ठा aa_loaddata *
__aa_get_loaddata(काष्ठा aa_loaddata *data)
अणु
	अगर (data && kref_get_unless_zero(&(data->count)))
		वापस data;

	वापस शून्य;
पूर्ण

/**
 * aa_get_loaddata - get a reference count from a counted data reference
 * @data: reference to get a count on
 *
 * Returns: poपूर्णांक to reference
 * Requires: @data to have a valid reference count on it. It is a bug
 *           अगर the race to reap can be encountered when it is used.
 */
अटल अंतरभूत काष्ठा aa_loaddata *
aa_get_loaddata(काष्ठा aa_loaddata *data)
अणु
	काष्ठा aa_loaddata *पंचांगp = __aa_get_loaddata(data);

	AA_BUG(data && !पंचांगp);

	वापस पंचांगp;
पूर्ण

व्योम __aa_loaddata_update(काष्ठा aa_loaddata *data, दीर्घ revision);
bool aa_rawdata_eq(काष्ठा aa_loaddata *l, काष्ठा aa_loaddata *r);
व्योम aa_loaddata_kref(काष्ठा kref *kref);
काष्ठा aa_loaddata *aa_loaddata_alloc(माप_प्रकार size);
अटल अंतरभूत व्योम aa_put_loaddata(काष्ठा aa_loaddata *data)
अणु
	अगर (data)
		kref_put(&data->count, aa_loaddata_kref);
पूर्ण

#पूर्ण_अगर /* __POLICY_INTERFACE_H */
