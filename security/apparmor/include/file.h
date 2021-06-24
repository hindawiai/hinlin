<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor file mediation function definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#अगर_अघोषित __AA_खाता_H
#घोषणा __AA_खाता_H

#समावेश <linux/spinlock.h>

#समावेश "domain.h"
#समावेश "match.h"
#समावेश "perms.h"

काष्ठा aa_profile;
काष्ठा path;

#घोषणा mask_mode_t(X) (X & (MAY_EXEC | MAY_WRITE | MAY_READ | MAY_APPEND))

#घोषणा AA_AUDIT_खाता_MASK	(MAY_READ | MAY_WRITE | MAY_EXEC | MAY_APPEND |\
				 AA_MAY_CREATE | AA_MAY_DELETE |	\
				 AA_MAY_GETATTR | AA_MAY_SETATTR | \
				 AA_MAY_CHMOD | AA_MAY_CHOWN | AA_MAY_LOCK | \
				 AA_EXEC_MMAP | AA_MAY_LINK)

अटल अंतरभूत काष्ठा aa_file_ctx *file_ctx(काष्ठा file *file)
अणु
	वापस file->f_security + apparmor_blob_sizes.lbs_file;
पूर्ण

/* काष्ठा aa_file_ctx - the AppArmor context the file was खोलोed in
 * @lock: lock to update the ctx
 * @label: label currently cached on the ctx
 * @perms: the permission the file was खोलोed with
 */
काष्ठा aa_file_ctx अणु
	spinlock_t lock;
	काष्ठा aa_label __rcu *label;
	u32 allow;
पूर्ण;

/**
 * aa_alloc_file_ctx - allocate file_ctx
 * @label: initial label of task creating the file
 * @gfp: gfp flags क्रम allocation
 *
 * Returns: file_ctx or शून्य on failure
 */
अटल अंतरभूत काष्ठा aa_file_ctx *aa_alloc_file_ctx(काष्ठा aa_label *label,
						    gfp_t gfp)
अणु
	काष्ठा aa_file_ctx *ctx;

	ctx = kzalloc(माप(काष्ठा aa_file_ctx), gfp);
	अगर (ctx) अणु
		spin_lock_init(&ctx->lock);
		rcu_assign_poपूर्णांकer(ctx->label, aa_get_label(label));
	पूर्ण
	वापस ctx;
पूर्ण

/**
 * aa_मुक्त_file_ctx - मुक्त a file_ctx
 * @ctx: file_ctx to मुक्त  (MAYBE_शून्य)
 */
अटल अंतरभूत व्योम aa_मुक्त_file_ctx(काष्ठा aa_file_ctx *ctx)
अणु
	अगर (ctx) अणु
		aa_put_label(rcu_access_poपूर्णांकer(ctx->label));
		kमुक्त_sensitive(ctx);
	पूर्ण
पूर्ण

अटल अंतरभूत काष्ठा aa_label *aa_get_file_label(काष्ठा aa_file_ctx *ctx)
अणु
	वापस aa_get_label_rcu(&ctx->label);
पूर्ण

/*
 * The xindex is broken पूर्णांकo 3 parts
 * - index - an index पूर्णांकo either the exec name table or the variable table
 * - exec type - which determines how the executable name and index are used
 * - flags - which modअगरy how the destination name is applied
 */
#घोषणा AA_X_INDEX_MASK		0x03ff

#घोषणा AA_X_TYPE_MASK		0x0c00
#घोषणा AA_X_TYPE_SHIFT		10
#घोषणा AA_X_NONE		0x0000
#घोषणा AA_X_NAME		0x0400	/* use executable name px */
#घोषणा AA_X_TABLE		0x0800	/* use a specअगरied name ->n# */

#घोषणा AA_X_UNSAFE		0x1000
#घोषणा AA_X_CHILD		0x2000	/* make >AA_X_NONE apply to children */
#घोषणा AA_X_INHERIT		0x4000
#घोषणा AA_X_UNCONFINED		0x8000

/* need to make conditional which ones are being set */
काष्ठा path_cond अणु
	kuid_t uid;
	umode_t mode;
पूर्ण;

#घोषणा COMBINED_PERM_MASK(X) ((X).allow | (X).audit | (X).quiet | (X).समाप्त)

/* FIXME: split perms from dfa and match this to description
 *        also add delegation info.
 */
अटल अंतरभूत u16 dfa_map_xindex(u16 mask)
अणु
	u16 old_index = (mask >> 10) & 0xf;
	u16 index = 0;

	अगर (mask & 0x100)
		index |= AA_X_UNSAFE;
	अगर (mask & 0x200)
		index |= AA_X_INHERIT;
	अगर (mask & 0x80)
		index |= AA_X_UNCONFINED;

	अगर (old_index == 1) अणु
		index |= AA_X_UNCONFINED;
	पूर्ण अन्यथा अगर (old_index == 2) अणु
		index |= AA_X_NAME;
	पूर्ण अन्यथा अगर (old_index == 3) अणु
		index |= AA_X_NAME | AA_X_CHILD;
	पूर्ण अन्यथा अगर (old_index) अणु
		index |= AA_X_TABLE;
		index |= old_index - 4;
	पूर्ण

	वापस index;
पूर्ण

/*
 * map old dfa अंतरभूत permissions to new क्रमmat
 */
#घोषणा dfa_user_allow(dfa, state) (((ACCEPT_TABLE(dfa)[state]) & 0x7f) | \
				    ((ACCEPT_TABLE(dfa)[state]) & 0x80000000))
#घोषणा dfa_user_audit(dfa, state) ((ACCEPT_TABLE2(dfa)[state]) & 0x7f)
#घोषणा dfa_user_quiet(dfa, state) (((ACCEPT_TABLE2(dfa)[state]) >> 7) & 0x7f)
#घोषणा dfa_user_xindex(dfa, state) \
	(dfa_map_xindex(ACCEPT_TABLE(dfa)[state] & 0x3fff))

#घोषणा dfa_other_allow(dfa, state) ((((ACCEPT_TABLE(dfa)[state]) >> 14) & \
				      0x7f) |				\
				     ((ACCEPT_TABLE(dfa)[state]) & 0x80000000))
#घोषणा dfa_other_audit(dfa, state) (((ACCEPT_TABLE2(dfa)[state]) >> 14) & 0x7f)
#घोषणा dfa_other_quiet(dfa, state) \
	((((ACCEPT_TABLE2(dfa)[state]) >> 7) >> 14) & 0x7f)
#घोषणा dfa_other_xindex(dfa, state) \
	dfa_map_xindex((ACCEPT_TABLE(dfa)[state] >> 14) & 0x3fff)

पूर्णांक aa_audit_file(काष्ठा aa_profile *profile, काष्ठा aa_perms *perms,
		  स्थिर अक्षर *op, u32 request, स्थिर अक्षर *name,
		  स्थिर अक्षर *target, काष्ठा aa_label *tlabel, kuid_t ouid,
		  स्थिर अक्षर *info, पूर्णांक error);

/**
 * काष्ठा aa_file_rules - components used क्रम file rule permissions
 * @dfa: dfa to match path names and conditionals against
 * @perms: permission table indexed by the matched state accept entry of @dfa
 * @trans: transition table क्रम indexed by named x transitions
 *
 * File permission are determined by matching a path against @dfa and then
 * then using the value of the accept entry क्रम the matching state as
 * an index पूर्णांकo @perms.  If a named exec transition is required it is
 * looked up in the transition table.
 */
काष्ठा aa_file_rules अणु
	अचिन्हित पूर्णांक start;
	काष्ठा aa_dfa *dfa;
	/* काष्ठा perms perms; */
	काष्ठा aa_करोमुख्य trans;
	/* TODO: add delegate table */
पूर्ण;

काष्ठा aa_perms aa_compute_fperms(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक state,
				    काष्ठा path_cond *cond);
अचिन्हित पूर्णांक aa_str_perms(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
			  स्थिर अक्षर *name, काष्ठा path_cond *cond,
			  काष्ठा aa_perms *perms);

पूर्णांक __aa_path_perm(स्थिर अक्षर *op, काष्ठा aa_profile *profile,
		   स्थिर अक्षर *name, u32 request, काष्ठा path_cond *cond,
		   पूर्णांक flags, काष्ठा aa_perms *perms);
पूर्णांक aa_path_perm(स्थिर अक्षर *op, काष्ठा aa_label *label,
		 स्थिर काष्ठा path *path, पूर्णांक flags, u32 request,
		 काष्ठा path_cond *cond);

पूर्णांक aa_path_link(काष्ठा aa_label *label, काष्ठा dentry *old_dentry,
		 स्थिर काष्ठा path *new_dir, काष्ठा dentry *new_dentry);

पूर्णांक aa_file_perm(स्थिर अक्षर *op, काष्ठा aa_label *label, काष्ठा file *file,
		 u32 request, bool in_atomic);

व्योम aa_inherit_files(स्थिर काष्ठा cred *cred, काष्ठा files_काष्ठा *files);

अटल अंतरभूत व्योम aa_मुक्त_file_rules(काष्ठा aa_file_rules *rules)
अणु
	aa_put_dfa(rules->dfa);
	aa_मुक्त_करोमुख्य_entries(&rules->trans);
पूर्ण

/**
 * aa_map_file_perms - map file flags to AppArmor permissions
 * @file: खोलो file to map flags to AppArmor permissions
 *
 * Returns: apparmor permission set क्रम the file
 */
अटल अंतरभूत u32 aa_map_file_to_perms(काष्ठा file *file)
अणु
	पूर्णांक flags = file->f_flags;
	u32 perms = 0;

	अगर (file->f_mode & FMODE_WRITE)
		perms |= MAY_WRITE;
	अगर (file->f_mode & FMODE_READ)
		perms |= MAY_READ;

	अगर ((flags & O_APPEND) && (perms & MAY_WRITE))
		perms = (perms & ~MAY_WRITE) | MAY_APPEND;
	/* trunc implies ग_लिखो permission */
	अगर (flags & O_TRUNC)
		perms |= MAY_WRITE;
	अगर (flags & O_CREAT)
		perms |= AA_MAY_CREATE;

	वापस perms;
पूर्ण

#पूर्ण_अगर /* __AA_खाता_H */
