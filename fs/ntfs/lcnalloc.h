<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * lcnभाग.स - Exports क्रम NTFS kernel cluster (de)allocation.  Part of the
 *		Linux-NTFS project.
 *
 * Copyright (c) 2004-2005 Anton Altaparmakov
 */

#अगर_अघोषित _LINUX_NTFS_LCNALLOC_H
#घोषणा _LINUX_NTFS_LCNALLOC_H

#अगर_घोषित NTFS_RW

#समावेश <linux/fs.h>

#समावेश "attrib.h"
#समावेश "types.h"
#समावेश "inode.h"
#समावेश "runlist.h"
#समावेश "volume.h"

प्रकार क्रमागत अणु
	FIRST_ZONE	= 0,	/* For sanity checking. */
	MFT_ZONE	= 0,	/* Allocate from $MFT zone. */
	DATA_ZONE	= 1,	/* Allocate from $DATA zone. */
	LAST_ZONE	= 1,	/* For sanity checking. */
पूर्ण NTFS_CLUSTER_ALLOCATION_ZONES;

बाह्य runlist_element *ntfs_cluster_alloc(ntfs_volume *vol,
		स्थिर VCN start_vcn, स्थिर s64 count, स्थिर LCN start_lcn,
		स्थिर NTFS_CLUSTER_ALLOCATION_ZONES zone,
		स्थिर bool is_extension);

बाह्य s64 __ntfs_cluster_मुक्त(ntfs_inode *ni, स्थिर VCN start_vcn,
		s64 count, ntfs_attr_search_ctx *ctx, स्थिर bool is_rollback);

/**
 * ntfs_cluster_मुक्त - मुक्त clusters on an ntfs volume
 * @ni:		ntfs inode whose runlist describes the clusters to मुक्त
 * @start_vcn:	vcn in the runlist of @ni at which to start मुक्तing clusters
 * @count:	number of clusters to मुक्त or -1 क्रम all clusters
 * @ctx:	active attribute search context अगर present or शून्य अगर not
 *
 * Free @count clusters starting at the cluster @start_vcn in the runlist
 * described by the ntfs inode @ni.
 *
 * If @count is -1, all clusters from @start_vcn to the end of the runlist are
 * deallocated.  Thus, to completely मुक्त all clusters in a runlist, use
 * @start_vcn = 0 and @count = -1.
 *
 * If @ctx is specअगरied, it is an active search context of @ni and its base mft
 * record.  This is needed when ntfs_cluster_मुक्त() encounters unmapped runlist
 * fragments and allows their mapping.  If you करो not have the mft record
 * mapped, you can specअगरy @ctx as शून्य and ntfs_cluster_मुक्त() will perक्रमm
 * the necessary mapping and unmapping.
 *
 * Note, ntfs_cluster_मुक्त() saves the state of @ctx on entry and restores it
 * beक्रमe वापसing.  Thus, @ctx will be left poपूर्णांकing to the same attribute on
 * वापस as on entry.  However, the actual poपूर्णांकers in @ctx may poपूर्णांक to
 * dअगरferent memory locations on वापस, so you must remember to reset any
 * cached poपूर्णांकers from the @ctx, i.e. after the call to ntfs_cluster_मुक्त(),
 * you will probably want to करो:
 *	m = ctx->mrec;
 *	a = ctx->attr;
 * Assuming you cache ctx->attr in a variable @a of type ATTR_RECORD * and that
 * you cache ctx->mrec in a variable @m of type MFT_RECORD *.
 *
 * Note, ntfs_cluster_मुक्त() करोes not modअगरy the runlist, so you have to हटाओ
 * from the runlist or mark sparse the मुक्तd runs later.
 *
 * Return the number of deallocated clusters (not counting sparse ones) on
 * success and -त्रुटि_सं on error.
 *
 * WARNING: If @ctx is supplied, regardless of whether success or failure is
 *	    वापसed, you need to check IS_ERR(@ctx->mrec) and अगर 'true' the @ctx
 *	    is no दीर्घer valid, i.e. you need to either call
 *	    ntfs_attr_reinit_search_ctx() or ntfs_attr_put_search_ctx() on it.
 *	    In that हाल PTR_ERR(@ctx->mrec) will give you the error code क्रम
 *	    why the mapping of the old inode failed.
 *
 * Locking: - The runlist described by @ni must be locked क्रम writing on entry
 *	      and is locked on वापस.  Note the runlist may be modअगरied when
 *	      needed runlist fragments need to be mapped.
 *	    - The volume lcn biपंचांगap must be unlocked on entry and is unlocked
 *	      on वापस.
 *	    - This function takes the volume lcn biपंचांगap lock क्रम writing and
 *	      modअगरies the biपंचांगap contents.
 *	    - If @ctx is शून्य, the base mft record of @ni must not be mapped on
 *	      entry and it will be left unmapped on वापस.
 *	    - If @ctx is not शून्य, the base mft record must be mapped on entry
 *	      and it will be left mapped on वापस.
 */
अटल अंतरभूत s64 ntfs_cluster_मुक्त(ntfs_inode *ni, स्थिर VCN start_vcn,
		s64 count, ntfs_attr_search_ctx *ctx)
अणु
	वापस __ntfs_cluster_मुक्त(ni, start_vcn, count, ctx, false);
पूर्ण

बाह्य पूर्णांक ntfs_cluster_मुक्त_from_rl_nolock(ntfs_volume *vol,
		स्थिर runlist_element *rl);

/**
 * ntfs_cluster_मुक्त_from_rl - मुक्त clusters from runlist
 * @vol:	mounted ntfs volume on which to मुक्त the clusters
 * @rl:		runlist describing the clusters to मुक्त
 *
 * Free all the clusters described by the runlist @rl on the volume @vol.  In
 * the हाल of an error being वापसed, at least some of the clusters were not
 * मुक्तd.
 *
 * Return 0 on success and -त्रुटि_सं on error.
 *
 * Locking: - This function takes the volume lcn biपंचांगap lock क्रम writing and
 *	      modअगरies the biपंचांगap contents.
 *	    - The caller must have locked the runlist @rl क्रम पढ़ोing or
 *	      writing.
 */
अटल अंतरभूत पूर्णांक ntfs_cluster_मुक्त_from_rl(ntfs_volume *vol,
		स्थिर runlist_element *rl)
अणु
	पूर्णांक ret;

	करोwn_ग_लिखो(&vol->lcnbmp_lock);
	ret = ntfs_cluster_मुक्त_from_rl_nolock(vol, rl);
	up_ग_लिखो(&vol->lcnbmp_lock);
	वापस ret;
पूर्ण

#पूर्ण_अगर /* NTFS_RW */

#पूर्ण_अगर /* defined _LINUX_NTFS_LCNALLOC_H */
