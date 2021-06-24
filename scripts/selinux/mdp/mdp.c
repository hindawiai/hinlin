<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *
 * mdp - make dummy policy
 *
 * When poपूर्णांकed at a kernel tree, builds a dummy policy क्रम that kernel
 * with exactly one type with full rights to itself.
 *
 * Copyright (C) IBM Corporation, 2006
 *
 * Authors: Serge E. Hallyn <serue@us.ibm.com>
 */


/* NOTE: we really करो want to use the kernel headers here */
#घोषणा __EXPORTED_HEADERS__

#समावेश <मानकपन.स>
#समावेश <मानककोष.स>
#समावेश <unistd.h>
#समावेश <माला.स>
#समावेश <linux/kconfig.h>

अटल व्योम usage(अक्षर *name)
अणु
	म_लिखो("usage: %s [-m] policy_file context_file\n", name);
	निकास(1);
पूर्ण

/* Class/perm mapping support */
काष्ठा security_class_mapping अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *perms[माप(अचिन्हित) * 8 + 1];
पूर्ण;

#समावेश "classmap.h"
#समावेश "initial_sid_to_string.h"
#समावेश "policycap_names.h"

#घोषणा ARRAY_SIZE(arr) (माप(arr) / माप((arr)[0]))

पूर्णांक मुख्य(पूर्णांक argc, अक्षर *argv[])
अणु
	पूर्णांक i, j, mls = 0;
	पूर्णांक initial_sid_to_string_len;
	अक्षर **arg, *polout, *ctxout;

	खाता *fout;

	अगर (argc < 3)
		usage(argv[0]);
	arg = argv+1;
	अगर (argc==4 && म_भेद(argv[1], "-m") == 0) अणु
		mls = 1;
		arg++;
	पूर्ण
	polout = *arg++;
	ctxout = *arg;

	fout = ख_खोलो(polout, "w");
	अगर (!fout) अणु
		म_लिखो("Could not open %s for writing\n", polout);
		usage(argv[0]);
	पूर्ण

	/* prपूर्णांक out the classes */
	क्रम (i = 0; secclass_map[i].name; i++)
		ख_लिखो(fout, "class %s\n", secclass_map[i].name);
	ख_लिखो(fout, "\n");

	initial_sid_to_string_len = माप(initial_sid_to_string) / माप (अक्षर *);
	/* prपूर्णांक out the sids */
	क्रम (i = 1; i < initial_sid_to_string_len; i++) अणु
		स्थिर अक्षर *name = initial_sid_to_string[i];

		अगर (name)
			ख_लिखो(fout, "sid %s\n", name);
		अन्यथा
			ख_लिखो(fout, "sid unused%d\n", i);
	पूर्ण
	ख_लिखो(fout, "\n");

	/* prपूर्णांक out the class permissions */
	क्रम (i = 0; secclass_map[i].name; i++) अणु
		काष्ठा security_class_mapping *map = &secclass_map[i];
		ख_लिखो(fout, "class %s\n", map->name);
		ख_लिखो(fout, "{\n");
		क्रम (j = 0; map->perms[j]; j++)
			ख_लिखो(fout, "\t%s\n", map->perms[j]);
		ख_लिखो(fout, "}\n\n");
	पूर्ण
	ख_लिखो(fout, "\n");

	/* prपूर्णांक out mls declarations and स्थिरraपूर्णांकs */
	अगर (mls) अणु
		ख_लिखो(fout, "sensitivity s0;\n");
		ख_लिखो(fout, "sensitivity s1;\n");
		ख_लिखो(fout, "dominance { s0 s1 }\n");
		ख_लिखो(fout, "category c0;\n");
		ख_लिखो(fout, "category c1;\n");
		ख_लिखो(fout, "level s0:c0.c1;\n");
		ख_लिखो(fout, "level s1:c0.c1;\n");
#घोषणा SYSTEMLOW "s0"
#घोषणा SYSTEMHIGH "s1:c0.c1"
		क्रम (i = 0; secclass_map[i].name; i++) अणु
			काष्ठा security_class_mapping *map = &secclass_map[i];

			ख_लिखो(fout, "mlsconstrain %s {\n", map->name);
			क्रम (j = 0; map->perms[j]; j++)
				ख_लिखो(fout, "\t%s\n", map->perms[j]);
			/*
			 * This requires all subjects and objects to be
			 * single-level (l2 eq h2), and that the subject
			 * level करोminate the object level (h1 करोm h2)
			 * in order to have any permissions to it.
			 */
			ख_लिखो(fout, "} (l2 eq h2 and h1 dom h2);\n\n");
		पूर्ण
	पूर्ण

	/* enable all policy capabilities */
	क्रम (i = 0; i < ARRAY_SIZE(selinux_policycap_names); i++)
		ख_लिखो(fout, "policycap %s;\n", selinux_policycap_names[i]);

	/* types, roles, and allows */
	ख_लिखो(fout, "type base_t;\n");
	ख_लिखो(fout, "role base_r;\n");
	ख_लिखो(fout, "role base_r types { base_t };\n");
	क्रम (i = 0; secclass_map[i].name; i++)
		ख_लिखो(fout, "allow base_t base_t:%s *;\n",
			secclass_map[i].name);
	ख_लिखो(fout, "user user_u roles { base_r }");
	अगर (mls)
		ख_लिखो(fout, " level %s range %s - %s", SYSTEMLOW,
			SYSTEMLOW, SYSTEMHIGH);
	ख_लिखो(fout, ";\n");

#घोषणा SUBJUSERROLETYPE "user_u:base_r:base_t"
#घोषणा OBJUSERROLETYPE "user_u:object_r:base_t"

	/* शेष sids */
	क्रम (i = 1; i < initial_sid_to_string_len; i++) अणु
		स्थिर अक्षर *name = initial_sid_to_string[i];

		अगर (name)
			ख_लिखो(fout, "sid %s ", name);
		अन्यथा
			ख_लिखो(fout, "sid unused%d\n", i);
		ख_लिखो(fout, SUBJUSERROLETYPE "%s\n",
			mls ? ":" SYSTEMLOW : "");
	पूर्ण
	ख_लिखो(fout, "\n");

#घोषणा FS_USE(behavior, fstype)			    \
	ख_लिखो(fout, "fs_use_%s %s " OBJUSERROLETYPE "%s;\n", \
		behavior, fstype, mls ? ":" SYSTEMLOW : "")

	/*
	 * Fileप्रणालीs whose inode labels can be fetched via getxattr.
	 */
#अगर_घोषित CONFIG_EXT2_FS_SECURITY
	FS_USE("xattr", "ext2");
#पूर्ण_अगर
#अगर_घोषित CONFIG_EXT4_FS_SECURITY
#अगर_घोषित CONFIG_EXT4_USE_FOR_EXT2
	FS_USE("xattr", "ext2");
#पूर्ण_अगर
	FS_USE("xattr", "ext3");
	FS_USE("xattr", "ext4");
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFS_SECURITY
	FS_USE("xattr", "jfs");
#पूर्ण_अगर
#अगर_घोषित CONFIG_REISERFS_FS_SECURITY
	FS_USE("xattr", "reiserfs");
#पूर्ण_अगर
#अगर_घोषित CONFIG_JFFS2_FS_SECURITY
	FS_USE("xattr", "jffs2");
#पूर्ण_अगर
#अगर_घोषित CONFIG_XFS_FS
	FS_USE("xattr", "xfs");
#पूर्ण_अगर
#अगर_घोषित CONFIG_GFS2_FS
	FS_USE("xattr", "gfs2");
#पूर्ण_अगर
#अगर_घोषित CONFIG_BTRFS_FS
	FS_USE("xattr", "btrfs");
#पूर्ण_अगर
#अगर_घोषित CONFIG_F2FS_FS_SECURITY
	FS_USE("xattr", "f2fs");
#पूर्ण_अगर
#अगर_घोषित CONFIG_OCFS2_FS
	FS_USE("xattr", "ocsfs2");
#पूर्ण_अगर
#अगर_घोषित CONFIG_OVERLAY_FS
	FS_USE("xattr", "overlay");
#पूर्ण_अगर
#अगर_घोषित CONFIG_SQUASHFS_XATTR
	FS_USE("xattr", "squashfs");
#पूर्ण_अगर

	/*
	 * Fileप्रणालीs whose inodes are labeled from allocating task.
	 */
	FS_USE("task", "pipefs");
	FS_USE("task", "sockfs");

	/*
	 * Fileप्रणालीs whose inode labels are computed from both
	 * the allocating task and the superblock label.
	 */
#अगर_घोषित CONFIG_UNIX98_PTYS
	FS_USE("trans", "devpts");
#पूर्ण_अगर
#अगर_घोषित CONFIG_HUGETLBFS
	FS_USE("trans", "hugetlbfs");
#पूर्ण_अगर
#अगर_घोषित CONFIG_TMPFS
	FS_USE("trans", "tmpfs");
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEVTMPFS
	FS_USE("trans", "devtmpfs");
#पूर्ण_अगर
#अगर_घोषित CONFIG_POSIX_MQUEUE
	FS_USE("trans", "mqueue");
#पूर्ण_अगर

#घोषणा GENFSCON(fstype, prefix)			     \
	ख_लिखो(fout, "genfscon %s %s " OBJUSERROLETYPE "%s\n", \
		fstype, prefix, mls ? ":" SYSTEMLOW : "")

	/*
	 * Fileप्रणालीs whose inodes are labeled from path prefix match
	 * relative to the fileप्रणाली root.  Depending on the fileप्रणाली,
	 * only a single label क्रम all inodes may be supported.  Here
	 * we list the fileप्रणाली types क्रम which per-file labeling is
	 * supported using genfscon; any other fileप्रणाली type can also
	 * be added by only with a single entry क्रम all of its inodes.
	 */
#अगर_घोषित CONFIG_PROC_FS
	GENFSCON("proc", "/");
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY_SELINUX
	GENFSCON("selinuxfs", "/");
#पूर्ण_अगर
#अगर_घोषित CONFIG_SYSFS
	GENFSCON("sysfs", "/");
#पूर्ण_अगर
#अगर_घोषित CONFIG_DEBUG_FS
	GENFSCON("debugfs", "/");
#पूर्ण_अगर
#अगर_घोषित CONFIG_TRACING
	GENFSCON("tracefs", "/");
#पूर्ण_अगर
#अगर_घोषित CONFIG_PSTORE
	GENFSCON("pstore", "/");
#पूर्ण_अगर
	GENFSCON("cgroup", "/");
	GENFSCON("cgroup2", "/");

	ख_बंद(fout);

	fout = ख_खोलो(ctxout, "w");
	अगर (!fout) अणु
		म_लिखो("Wrote policy, but cannot open %s for writing\n", ctxout);
		usage(argv[0]);
	पूर्ण
	ख_लिखो(fout, "/ " OBJUSERROLETYPE "%s\n", mls ? ":" SYSTEMLOW : "");
	ख_लिखो(fout, "/.* " OBJUSERROLETYPE "%s\n", mls ? ":" SYSTEMLOW : "");
	ख_बंद(fout);

	वापस 0;
पूर्ण
