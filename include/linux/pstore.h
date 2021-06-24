<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Persistent Storage - pstore.h
 *
 * Copyright (C) 2010 Intel Corporation <tony.luck@पूर्णांकel.com>
 *
 * This code is the generic layer to export data records from platक्रमm
 * level persistent storage via a file प्रणाली.
 */
#अगर_अघोषित _LINUX_PSTORE_H
#घोषणा _LINUX_PSTORE_H

#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kmsg_dump.h>
#समावेश <linux/mutex.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/समय.स>
#समावेश <linux/types.h>

काष्ठा module;

/*
 * pstore record types (see fs/pstore/platक्रमm.c क्रम pstore_type_names[])
 * These values may be written to storage (see EFI vars backend), so
 * they are kind of an ABI. Be careful changing the mappings.
 */
क्रमागत pstore_type_id अणु
	/* Frontend storage types */
	PSTORE_TYPE_DMESG	= 0,
	PSTORE_TYPE_MCE		= 1,
	PSTORE_TYPE_CONSOLE	= 2,
	PSTORE_TYPE_FTRACE	= 3,

	/* PPC64-specअगरic partition types */
	PSTORE_TYPE_PPC_RTAS	= 4,
	PSTORE_TYPE_PPC_OF	= 5,
	PSTORE_TYPE_PPC_COMMON	= 6,
	PSTORE_TYPE_PMSG	= 7,
	PSTORE_TYPE_PPC_OPAL	= 8,

	/* End of the list */
	PSTORE_TYPE_MAX
पूर्ण;

स्थिर अक्षर *pstore_type_to_name(क्रमागत pstore_type_id type);
क्रमागत pstore_type_id pstore_name_to_type(स्थिर अक्षर *name);

काष्ठा pstore_info;
/**
 * काष्ठा pstore_record - details of a pstore record entry
 * @psi:	pstore backend driver inक्रमmation
 * @type:	pstore record type
 * @id:		per-type unique identअगरier क्रम record
 * @समय:	बारtamp of the record
 * @buf:	poपूर्णांकer to record contents
 * @size:	size of @buf
 * @ecc_notice_size:
 *		ECC inक्रमmation क्रम @buf
 *
 * Valid क्रम PSTORE_TYPE_DMESG @type:
 *
 * @count:	Oops count since boot
 * @reason:	kdump reason क्रम notअगरication
 * @part:	position in a multipart record
 * @compressed:	whether the buffer is compressed
 *
 */
काष्ठा pstore_record अणु
	काष्ठा pstore_info	*psi;
	क्रमागत pstore_type_id	type;
	u64			id;
	काष्ठा बारpec64	समय;
	अक्षर			*buf;
	sमाप_प्रकार			size;
	sमाप_प्रकार			ecc_notice_size;

	पूर्णांक			count;
	क्रमागत kmsg_dump_reason	reason;
	अचिन्हित पूर्णांक		part;
	bool			compressed;
पूर्ण;

/**
 * काष्ठा pstore_info - backend pstore driver काष्ठाure
 *
 * @owner:	module which is responsible क्रम this backend driver
 * @name:	name of the backend driver
 *
 * @buf_lock:	semaphore to serialize access to @buf
 * @buf:	pपुनः_स्मृतिated crash dump buffer
 * @bufsize:	size of @buf available क्रम crash dump bytes (must match
 *		smallest number of bytes available क्रम writing to a
 *		backend entry, since compressed bytes करोn't take kindly
 *		to being truncated)
 *
 * @पढ़ो_mutex:	serializes @खोलो, @पढ़ो, @बंद, and @erase callbacks
 * @flags:	bitfield of frontends the backend can accept ग_लिखोs क्रम
 * @max_reason:	Used when PSTORE_FLAGS_DMESG is set. Contains the
 *		kmsg_dump_reason क्रमागत value. KMSG_DUMP_UNDEF means
 *		"use existing kmsg_dump() filtering, based on the
 *		prपूर्णांकk.always_kmsg_dump boot param" (which is either
 *		KMSG_DUMP_OOPS when false, or KMSG_DUMP_MAX when
 *		true); see prपूर्णांकk.always_kmsg_dump क्रम more details.
 * @data:	backend-निजी poपूर्णांकer passed back during callbacks
 *
 * Callbacks:
 *
 * @खोलो:
 *	Notअगरy backend that pstore is starting a full पढ़ो of backend
 *	records. Followed by one or more @पढ़ो calls, and a final @बंद.
 *
 *	@psi:	in: poपूर्णांकer to the काष्ठा pstore_info क्रम the backend
 *
 *	Returns 0 on success, and non-zero on error.
 *
 * @बंद:
 *	Notअगरy backend that pstore has finished a full पढ़ो of backend
 *	records. Always preceded by an @खोलो call and one or more @पढ़ो
 *	calls.
 *
 *	@psi:	in: poपूर्णांकer to the काष्ठा pstore_info क्रम the backend
 *
 *	Returns 0 on success, and non-zero on error. (Though pstore will
 *	ignore the error.)
 *
 * @पढ़ो:
 *	Read next available backend record. Called after a successful
 *	@खोलो.
 *
 *	@record:
 *		poपूर्णांकer to record to populate. @buf should be allocated
 *		by the backend and filled. At least @type and @id should
 *		be populated, since these are used when creating pstorefs
 *		file names.
 *
 *	Returns record size on success, zero when no more records are
 *	available, or negative on error.
 *
 * @ग_लिखो:
 *	A newly generated record needs to be written to backend storage.
 *
 *	@record:
 *		poपूर्णांकer to record metadata. When @type is PSTORE_TYPE_DMESG,
 *		@buf will be poपूर्णांकing to the pपुनः_स्मृतिated @psi.buf, since
 *		memory allocation may be broken during an Oops. Regardless,
 *		@buf must be proccesed or copied beक्रमe वापसing. The
 *		backend is also expected to ग_लिखो @id with something that
 *		can help identअगरy this record to a future @erase callback.
 *		The @समय field will be prepopulated with the current समय,
 *		when available. The @size field will have the size of data
 *		in @buf.
 *
 *	Returns 0 on success, and non-zero on error.
 *
 * @ग_लिखो_user:
 *	Perक्रमm a frontend ग_लिखो to a backend record, using a specअगरied
 *	buffer that is coming directly from userspace, instead of the
 *	@record @buf.
 *
 *	@record:	poपूर्णांकer to record metadata.
 *	@buf:		poपूर्णांकer to userspace contents to ग_लिखो to backend
 *
 *	Returns 0 on success, and non-zero on error.
 *
 * @erase:
 *	Delete a record from backend storage.  Dअगरferent backends
 *	identअगरy records dअगरferently, so entire original record is
 *	passed back to assist in identअगरication of what the backend
 *	should हटाओ from storage.
 *
 *	@record:	poपूर्णांकer to record metadata.
 *
 *	Returns 0 on success, and non-zero on error.
 *
 */
काष्ठा pstore_info अणु
	काष्ठा module	*owner;
	स्थिर अक्षर	*name;

	काष्ठा semaphore buf_lock;
	अक्षर		*buf;
	माप_प्रकार		bufsize;

	काष्ठा mutex	पढ़ो_mutex;

	पूर्णांक		flags;
	पूर्णांक		max_reason;
	व्योम		*data;

	पूर्णांक		(*खोलो)(काष्ठा pstore_info *psi);
	पूर्णांक		(*बंद)(काष्ठा pstore_info *psi);
	sमाप_प्रकार		(*पढ़ो)(काष्ठा pstore_record *record);
	पूर्णांक		(*ग_लिखो)(काष्ठा pstore_record *record);
	पूर्णांक		(*ग_लिखो_user)(काष्ठा pstore_record *record,
				      स्थिर अक्षर __user *buf);
	पूर्णांक		(*erase)(काष्ठा pstore_record *record);
पूर्ण;

/* Supported frontends */
#घोषणा PSTORE_FLAGS_DMESG	BIT(0)
#घोषणा PSTORE_FLAGS_CONSOLE	BIT(1)
#घोषणा PSTORE_FLAGS_FTRACE	BIT(2)
#घोषणा PSTORE_FLAGS_PMSG	BIT(3)

बाह्य पूर्णांक pstore_रेजिस्टर(काष्ठा pstore_info *);
बाह्य व्योम pstore_unरेजिस्टर(काष्ठा pstore_info *);

काष्ठा pstore_ftrace_record अणु
	अचिन्हित दीर्घ ip;
	अचिन्हित दीर्घ parent_ip;
	u64 ts;
पूर्ण;

/*
 * ftrace related stuff: Both backends and frontends need these so expose
 * them here.
 */

#अगर NR_CPUS <= 2 && defined(CONFIG_ARM_THUMB)
#घोषणा PSTORE_CPU_IN_IP 0x1
#या_अगर NR_CPUS <= 4 && defined(CONFIG_ARM)
#घोषणा PSTORE_CPU_IN_IP 0x3
#पूर्ण_अगर

#घोषणा TS_CPU_SHIFT 8
#घोषणा TS_CPU_MASK (BIT(TS_CPU_SHIFT) - 1)

/*
 * If CPU number can be stored in IP, store it there, otherwise store it in
 * the समय stamp. This means more बारtamp resolution is available when
 * the CPU can be stored in the IP.
 */
#अगर_घोषित PSTORE_CPU_IN_IP
अटल अंतरभूत व्योम
pstore_ftrace_encode_cpu(काष्ठा pstore_ftrace_record *rec, अचिन्हित पूर्णांक cpu)
अणु
	rec->ip |= cpu;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
pstore_ftrace_decode_cpu(काष्ठा pstore_ftrace_record *rec)
अणु
	वापस rec->ip & PSTORE_CPU_IN_IP;
पूर्ण

अटल अंतरभूत u64
pstore_ftrace_पढ़ो_बारtamp(काष्ठा pstore_ftrace_record *rec)
अणु
	वापस rec->ts;
पूर्ण

अटल अंतरभूत व्योम
pstore_ftrace_ग_लिखो_बारtamp(काष्ठा pstore_ftrace_record *rec, u64 val)
अणु
	rec->ts = val;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
pstore_ftrace_encode_cpu(काष्ठा pstore_ftrace_record *rec, अचिन्हित पूर्णांक cpu)
अणु
	rec->ts &= ~(TS_CPU_MASK);
	rec->ts |= cpu;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक
pstore_ftrace_decode_cpu(काष्ठा pstore_ftrace_record *rec)
अणु
	वापस rec->ts & TS_CPU_MASK;
पूर्ण

अटल अंतरभूत u64
pstore_ftrace_पढ़ो_बारtamp(काष्ठा pstore_ftrace_record *rec)
अणु
	वापस rec->ts >> TS_CPU_SHIFT;
पूर्ण

अटल अंतरभूत व्योम
pstore_ftrace_ग_लिखो_बारtamp(काष्ठा pstore_ftrace_record *rec, u64 val)
अणु
	rec->ts = (rec->ts & TS_CPU_MASK) | (val << TS_CPU_SHIFT);
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /*_LINUX_PSTORE_H*/
