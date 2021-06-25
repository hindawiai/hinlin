<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * ocfs2_lockid.h
 *
 * Defines OCFS2 lockid bits.
 *
 * Copyright (C) 2002, 2005 Oracle.  All rights reserved.
 */

#अगर_अघोषित OCFS2_LOCKID_H
#घोषणा OCFS2_LOCKID_H

/* lock ids are made up in the following manner:
 * name[0]     --> type
 * name[1-6]   --> 6 pad अक्षरacters, reserved क्रम now
 * name[7-22]  --> block number, expressed in hex as 16 अक्षरs
 * name[23-30] --> i_generation, expressed in hex 8 अक्षरs
 * name[31]    --> '\0' */
#घोषणा OCFS2_LOCK_ID_MAX_LEN  32
#घोषणा OCFS2_LOCK_ID_PAD "000000"

#घोषणा OCFS2_DENTRY_LOCK_INO_START 18

क्रमागत ocfs2_lock_type अणु
	OCFS2_LOCK_TYPE_META = 0,
	OCFS2_LOCK_TYPE_DATA,
	OCFS2_LOCK_TYPE_SUPER,
	OCFS2_LOCK_TYPE_RENAME,
	OCFS2_LOCK_TYPE_RW,
	OCFS2_LOCK_TYPE_DENTRY,
	OCFS2_LOCK_TYPE_OPEN,
	OCFS2_LOCK_TYPE_FLOCK,
	OCFS2_LOCK_TYPE_QINFO,
	OCFS2_LOCK_TYPE_NFS_SYNC,
	OCFS2_LOCK_TYPE_ORPHAN_SCAN,
	OCFS2_LOCK_TYPE_REFCOUNT,
	OCFS2_LOCK_TYPE_TRIM_FS,
	OCFS2_NUM_LOCK_TYPES
पूर्ण;

अटल अंतरभूत अक्षर ocfs2_lock_type_अक्षर(क्रमागत ocfs2_lock_type type)
अणु
	अक्षर c;
	चयन (type) अणु
		हाल OCFS2_LOCK_TYPE_META:
			c = 'M';
			अवरोध;
		हाल OCFS2_LOCK_TYPE_DATA:
			c = 'D';
			अवरोध;
		हाल OCFS2_LOCK_TYPE_SUPER:
			c = 'S';
			अवरोध;
		हाल OCFS2_LOCK_TYPE_RENAME:
			c = 'R';
			अवरोध;
		हाल OCFS2_LOCK_TYPE_RW:
			c = 'W';
			अवरोध;
		हाल OCFS2_LOCK_TYPE_DENTRY:
			c = 'N';
			अवरोध;
		हाल OCFS2_LOCK_TYPE_OPEN:
			c = 'O';
			अवरोध;
		हाल OCFS2_LOCK_TYPE_FLOCK:
			c = 'F';
			अवरोध;
		हाल OCFS2_LOCK_TYPE_QINFO:
			c = 'Q';
			अवरोध;
		हाल OCFS2_LOCK_TYPE_NFS_SYNC:
			c = 'Y';
			अवरोध;
		हाल OCFS2_LOCK_TYPE_ORPHAN_SCAN:
			c = 'P';
			अवरोध;
		हाल OCFS2_LOCK_TYPE_REFCOUNT:
			c = 'T';
			अवरोध;
		हाल OCFS2_LOCK_TYPE_TRIM_FS:
			c = 'I';
			अवरोध;
		शेष:
			c = '\0';
	पूर्ण

	वापस c;
पूर्ण

अटल अक्षर *ocfs2_lock_type_strings[] = अणु
	[OCFS2_LOCK_TYPE_META] = "Meta",
	[OCFS2_LOCK_TYPE_DATA] = "Data",
	[OCFS2_LOCK_TYPE_SUPER] = "Super",
	[OCFS2_LOCK_TYPE_RENAME] = "Rename",
	/* Need to dअगरferntiate from [R]ename.. serializing ग_लिखोs is the
	 * important job it करोes, anyway. */
	[OCFS2_LOCK_TYPE_RW] = "Write/Read",
	[OCFS2_LOCK_TYPE_DENTRY] = "Dentry",
	[OCFS2_LOCK_TYPE_OPEN] = "Open",
	[OCFS2_LOCK_TYPE_FLOCK] = "Flock",
	[OCFS2_LOCK_TYPE_QINFO] = "Quota",
	[OCFS2_LOCK_TYPE_NFS_SYNC] = "NFSSync",
	[OCFS2_LOCK_TYPE_ORPHAN_SCAN] = "OrphanScan",
	[OCFS2_LOCK_TYPE_REFCOUNT] = "Refcount",
	[OCFS2_LOCK_TYPE_TRIM_FS] = "TrimFs",
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *ocfs2_lock_type_string(क्रमागत ocfs2_lock_type type)
अणु
#अगर_घोषित __KERNEL__
	BUG_ON(type >= OCFS2_NUM_LOCK_TYPES);
#पूर्ण_अगर
	वापस ocfs2_lock_type_strings[type];
पूर्ण

#पूर्ण_अगर  /* OCFS2_LOCKID_H */
