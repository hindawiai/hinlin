<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor fileप्रणाली definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#अगर_अघोषित __AA_APPARMORFS_H
#घोषणा __AA_APPARMORFS_H

बाह्य काष्ठा path aa_null;

क्रमागत aa_sfs_type अणु
	AA_SFS_TYPE_BOOLEAN,
	AA_SFS_TYPE_STRING,
	AA_SFS_TYPE_U64,
	AA_SFS_TYPE_FOPS,
	AA_SFS_TYPE_सूची,
पूर्ण;

काष्ठा aa_sfs_entry;

काष्ठा aa_sfs_entry अणु
	स्थिर अक्षर *name;
	काष्ठा dentry *dentry;
	umode_t mode;
	क्रमागत aa_sfs_type v_type;
	जोड़ अणु
		bool boolean;
		अक्षर *string;
		अचिन्हित दीर्घ u64;
		काष्ठा aa_sfs_entry *files;
	पूर्ण v;
	स्थिर काष्ठा file_operations *file_ops;
पूर्ण;

बाह्य स्थिर काष्ठा file_operations aa_sfs_seq_file_ops;

#घोषणा AA_SFS_खाता_BOOLEAN(_name, _value) \
	अणु .name = (_name), .mode = 0444, \
	  .v_type = AA_SFS_TYPE_BOOLEAN, .v.boolean = (_value), \
	  .file_ops = &aa_sfs_seq_file_ops पूर्ण
#घोषणा AA_SFS_खाता_STRING(_name, _value) \
	अणु .name = (_name), .mode = 0444, \
	  .v_type = AA_SFS_TYPE_STRING, .v.string = (_value), \
	  .file_ops = &aa_sfs_seq_file_ops पूर्ण
#घोषणा AA_SFS_खाता_U64(_name, _value) \
	अणु .name = (_name), .mode = 0444, \
	  .v_type = AA_SFS_TYPE_U64, .v.u64 = (_value), \
	  .file_ops = &aa_sfs_seq_file_ops पूर्ण
#घोषणा AA_SFS_खाता_FOPS(_name, _mode, _fops) \
	अणु .name = (_name), .v_type = AA_SFS_TYPE_FOPS, \
	  .mode = (_mode), .file_ops = (_fops) पूर्ण
#घोषणा AA_SFS_सूची(_name, _value) \
	अणु .name = (_name), .v_type = AA_SFS_TYPE_सूची, .v.files = (_value) पूर्ण

बाह्य व्योम __init aa_destroy_aafs(व्योम);

काष्ठा aa_profile;
काष्ठा aa_ns;

क्रमागत aafs_ns_type अणु
	AAFS_NS_सूची,
	AAFS_NS_PROFS,
	AAFS_NS_NS,
	AAFS_NS_RAW_DATA,
	AAFS_NS_LOAD,
	AAFS_NS_REPLACE,
	AAFS_NS_REMOVE,
	AAFS_NS_REVISION,
	AAFS_NS_COUNT,
	AAFS_NS_MAX_COUNT,
	AAFS_NS_SIZE,
	AAFS_NS_MAX_SIZE,
	AAFS_NS_OWNER,
	AAFS_NS_SIZखातापूर्ण,
पूर्ण;

क्रमागत aafs_prof_type अणु
	AAFS_PROF_सूची,
	AAFS_PROF_PROFS,
	AAFS_PROF_NAME,
	AAFS_PROF_MODE,
	AAFS_PROF_ATTACH,
	AAFS_PROF_HASH,
	AAFS_PROF_RAW_DATA,
	AAFS_PROF_RAW_HASH,
	AAFS_PROF_RAW_ABI,
	AAFS_PROF_SIZखातापूर्ण,
पूर्ण;

#घोषणा ns_dir(X) ((X)->dents[AAFS_NS_सूची])
#घोषणा ns_subns_dir(X) ((X)->dents[AAFS_NS_NS])
#घोषणा ns_subprofs_dir(X) ((X)->dents[AAFS_NS_PROFS])
#घोषणा ns_subdata_dir(X) ((X)->dents[AAFS_NS_RAW_DATA])
#घोषणा ns_subload(X) ((X)->dents[AAFS_NS_LOAD])
#घोषणा ns_subreplace(X) ((X)->dents[AAFS_NS_REPLACE])
#घोषणा ns_subहटाओ(X) ((X)->dents[AAFS_NS_REMOVE])
#घोषणा ns_subrevision(X) ((X)->dents[AAFS_NS_REVISION])

#घोषणा prof_dir(X) ((X)->dents[AAFS_PROF_सूची])
#घोषणा prof_child_dir(X) ((X)->dents[AAFS_PROF_PROFS])

व्योम __aa_bump_ns_revision(काष्ठा aa_ns *ns);
व्योम __aafs_profile_सूची_हटाओ(काष्ठा aa_profile *profile);
व्योम __aafs_profile_migrate_dents(काष्ठा aa_profile *old,
				   काष्ठा aa_profile *new);
पूर्णांक __aafs_profile_सूची_गढ़ो(काष्ठा aa_profile *profile, काष्ठा dentry *parent);
व्योम __aafs_ns_सूची_हटाओ(काष्ठा aa_ns *ns);
पूर्णांक __aafs_ns_सूची_गढ़ो(काष्ठा aa_ns *ns, काष्ठा dentry *parent, स्थिर अक्षर *name,
		     काष्ठा dentry *dent);

काष्ठा aa_loaddata;
व्योम __aa_fs_हटाओ_rawdata(काष्ठा aa_loaddata *rawdata);
पूर्णांक __aa_fs_create_rawdata(काष्ठा aa_ns *ns, काष्ठा aa_loaddata *rawdata);

#पूर्ण_अगर /* __AA_APPARMORFS_H */
