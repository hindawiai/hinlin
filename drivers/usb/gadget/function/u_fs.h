<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * u_fs.h
 *
 * Utility definitions क्रम the FunctionFS
 *
 * Copyright (c) 2013 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#अगर_अघोषित U_FFS_H
#घोषणा U_FFS_H

#समावेश <linux/usb/composite.h>
#समावेश <linux/list.h>
#समावेश <linux/mutex.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/refcount.h>

#अगर_घोषित VERBOSE_DEBUG
#अगर_अघोषित pr_vdebug
#  define pr_vdebug pr_debug
#पूर्ण_अगर /* pr_vdebug */
#  define ffs_dump_mem(prefix, ptr, len) \
	prपूर्णांक_hex_dump_bytes(pr_fmt(prefix ": "), DUMP_PREFIX_NONE, ptr, len)
#अन्यथा
#अगर_अघोषित pr_vdebug
#  define pr_vdebug(...)                 करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* pr_vdebug */
#  define ffs_dump_mem(prefix, ptr, len) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर /* VERBOSE_DEBUG */

#घोषणा ENTER()    pr_vdebug("%s()\n", __func__)

काष्ठा f_fs_opts;

काष्ठा ffs_dev अणु
	काष्ठा ffs_data *ffs_data;
	काष्ठा f_fs_opts *opts;
	काष्ठा list_head entry;

	अक्षर name[41];

	bool mounted;
	bool desc_पढ़ोy;
	bool single;

	पूर्णांक (*ffs_पढ़ोy_callback)(काष्ठा ffs_data *ffs);
	व्योम (*ffs_बंदd_callback)(काष्ठा ffs_data *ffs);
	व्योम *(*ffs_acquire_dev_callback)(काष्ठा ffs_dev *dev);
	व्योम (*ffs_release_dev_callback)(काष्ठा ffs_dev *dev);
पूर्ण;

बाह्य काष्ठा mutex ffs_lock;

अटल अंतरभूत व्योम ffs_dev_lock(व्योम)
अणु
	mutex_lock(&ffs_lock);
पूर्ण

अटल अंतरभूत व्योम ffs_dev_unlock(व्योम)
अणु
	mutex_unlock(&ffs_lock);
पूर्ण

पूर्णांक ffs_name_dev(काष्ठा ffs_dev *dev, स्थिर अक्षर *name);
पूर्णांक ffs_single_dev(काष्ठा ffs_dev *dev);

काष्ठा ffs_epfile;
काष्ठा ffs_function;

क्रमागत ffs_state अणु
	/*
	 * Waiting क्रम descriptors and strings.
	 *
	 * In this state no खोलो(2), पढ़ो(2) or ग_लिखो(2) on epfiles
	 * may succeed (which should not be the problem as there
	 * should be no such files खोलोed in the first place).
	 */
	FFS_READ_DESCRIPTORS,
	FFS_READ_STRINGS,

	/*
	 * We've got descriptors and strings.  We are or have called
	 * functionfs_पढ़ोy_callback().  functionfs_bind() may have
	 * been called but we करोn't know.
	 *
	 * This is the only state in which operations on epfiles may
	 * succeed.
	 */
	FFS_ACTIVE,

	/*
	 * Function is visible to host, but it's not functional. All
	 * setup requests are stalled and transfers on another endpoपूर्णांकs
	 * are refused. All epfiles, except ep0, are deleted so there
	 * is no way to perक्रमm any operations on them.
	 *
	 * This state is set after closing all functionfs files, when
	 * mount parameter "no_disconnect=1" has been set. Function will
	 * reमुख्य in deactivated state until fileप्रणाली is umounted or
	 * ep0 is खोलोed again. In the second हाल functionfs state will
	 * be reset, and it will be पढ़ोy क्रम descriptors and strings
	 * writing.
	 *
	 * This is useful only when functionfs is composed to gadget
	 * with another function which can perक्रमm some critical
	 * operations, and it's strongly desired to have this operations
	 * completed, even after functionfs files closure.
	 */
	FFS_DEACTIVATED,

	/*
	 * All endpoपूर्णांकs have been बंदd.  This state is also set अगर
	 * we encounter an unrecoverable error.  The only
	 * unrecoverable error is situation when after पढ़ोing strings
	 * from user space we fail to initialise epfiles or
	 * functionfs_पढ़ोy_callback() वापसs with error (<0).
	 *
	 * In this state no खोलो(2), पढ़ो(2) or ग_लिखो(2) (both on ep0
	 * as well as epfile) may succeed (at this poपूर्णांक epfiles are
	 * unlinked and all बंदd so this is not a problem; ep0 is
	 * also बंदd but ep0 file exists and so खोलो(2) on ep0 must
	 * fail).
	 */
	FFS_CLOSING
पूर्ण;

क्रमागत ffs_setup_state अणु
	/* There is no setup request pending. */
	FFS_NO_SETUP,
	/*
	 * User has पढ़ो events and there was a setup request event
	 * there.  The next पढ़ो/ग_लिखो on ep0 will handle the
	 * request.
	 */
	FFS_SETUP_PENDING,
	/*
	 * There was event pending but beक्रमe user space handled it
	 * some other event was पूर्णांकroduced which canceled existing
	 * setup.  If this state is set पढ़ो/ग_लिखो on ep0 वापस
	 * -EIDRM.  This state is only set when adding event.
	 */
	FFS_SETUP_CANCELLED
पूर्ण;

काष्ठा ffs_data अणु
	काष्ठा usb_gadget		*gadget;

	/*
	 * Protect access पढ़ो/ग_लिखो operations, only one पढ़ो/ग_लिखो
	 * at a समय.  As a consequence protects ep0req and company.
	 * While setup request is being processed (queued) this is
	 * held.
	 */
	काष्ठा mutex			mutex;

	/*
	 * Protect access to endpoपूर्णांक related काष्ठाures (basically
	 * usb_ep_queue(), usb_ep_dequeue(), etc. calls) except क्रम
	 * endpoपूर्णांक zero.
	 */
	spinlock_t			eps_lock;

	/*
	 * XXX REVISIT करो we need our own request? Since we are not
	 * handling setup requests immediately user space may be so
	 * slow that another setup will be sent to the gadget but this
	 * समय not to us but another function and then there could be
	 * a race.  Is that the हाल? Or maybe we can use cdev->req
	 * after all, maybe we just need some spinlock क्रम that?
	 */
	काष्ठा usb_request		*ep0req;		/* P: mutex */
	काष्ठा completion		ep0req_completion;	/* P: mutex */

	/* reference counter */
	refcount_t			ref;
	/* how many files are खोलोed (EP0 and others) */
	atomic_t			खोलोed;

	/* EP0 state */
	क्रमागत ffs_state			state;

	/*
	 * Possible transitions:
	 * + FFS_NO_SETUP        -> FFS_SETUP_PENDING  -- P: ev.रुकोq.lock
	 *               happens only in ep0 पढ़ो which is P: mutex
	 * + FFS_SETUP_PENDING   -> FFS_NO_SETUP       -- P: ev.रुकोq.lock
	 *               happens only in ep0 i/o  which is P: mutex
	 * + FFS_SETUP_PENDING   -> FFS_SETUP_CANCELLED -- P: ev.रुकोq.lock
	 * + FFS_SETUP_CANCELLED -> FFS_NO_SETUP        -- cmpxchg
	 *
	 * This field should never be accessed directly and instead
	 * ffs_setup_state_clear_cancelled function should be used.
	 */
	क्रमागत ffs_setup_state		setup_state;

	/* Events & such. */
	काष्ठा अणु
		u8				types[4];
		अचिन्हित लघु			count;
		/* XXX REVISIT need to update it in some places, or करो we? */
		अचिन्हित लघु			can_stall;
		काष्ठा usb_ctrlrequest		setup;

		रुको_queue_head_t		रुकोq;
	पूर्ण ev; /* the whole काष्ठाure, P: ev.रुकोq.lock */

	/* Flags */
	अचिन्हित दीर्घ			flags;
#घोषणा FFS_FL_CALL_CLOSED_CALLBACK 0
#घोषणा FFS_FL_BOUND                1

	/* For waking up blocked thपढ़ोs when function is enabled. */
	रुको_queue_head_t		रुको;

	/* Active function */
	काष्ठा ffs_function		*func;

	/*
	 * Device name, ग_लिखो once when file प्रणाली is mounted.
	 * Intended क्रम user to पढ़ो अगर she wants.
	 */
	स्थिर अक्षर			*dev_name;
	/* Private data क्रम our user (ie. gadget).  Managed by user. */
	व्योम				*निजी_data;

	/* filled by __ffs_data_got_descs() */
	/*
	 * raw_descs is what you kमुक्त, real_descs poपूर्णांकs inside of raw_descs,
	 * where full speed, high speed and super speed descriptors start.
	 * real_descs_length is the length of all those descriptors.
	 */
	स्थिर व्योम			*raw_descs_data;
	स्थिर व्योम			*raw_descs;
	अचिन्हित			raw_descs_length;
	अचिन्हित			fs_descs_count;
	अचिन्हित			hs_descs_count;
	अचिन्हित			ss_descs_count;
	अचिन्हित			ms_os_descs_count;
	अचिन्हित			ms_os_descs_ext_prop_count;
	अचिन्हित			ms_os_descs_ext_prop_name_len;
	अचिन्हित			ms_os_descs_ext_prop_data_len;
	व्योम				*ms_os_descs_ext_prop_avail;
	व्योम				*ms_os_descs_ext_prop_name_avail;
	व्योम				*ms_os_descs_ext_prop_data_avail;

	अचिन्हित			user_flags;

#घोषणा FFS_MAX_EPS_COUNT 31
	u8				eps_addrmap[FFS_MAX_EPS_COUNT];

	अचिन्हित लघु			strings_count;
	अचिन्हित लघु			पूर्णांकerfaces_count;
	अचिन्हित लघु			eps_count;
	अचिन्हित लघु			_pad1;

	/* filled by __ffs_data_got_strings() */
	/* ids in stringtअसल are set in functionfs_bind() */
	स्थिर व्योम			*raw_strings;
	काष्ठा usb_gadget_strings	**stringtअसल;

	/*
	 * File प्रणाली's super block, ग_लिखो once when file प्रणाली is
	 * mounted.
	 */
	काष्ठा super_block		*sb;

	/* File permissions, written once when fs is mounted */
	काष्ठा ffs_file_perms अणु
		umode_t				mode;
		kuid_t				uid;
		kgid_t				gid;
	पूर्ण				file_perms;

	काष्ठा eventfd_ctx *ffs_eventfd;
	काष्ठा workqueue_काष्ठा *io_completion_wq;
	bool no_disconnect;
	काष्ठा work_काष्ठा reset_work;

	/*
	 * The endpoपूर्णांक files, filled by ffs_epfiles_create(),
	 * destroyed by ffs_epfiles_destroy().
	 */
	काष्ठा ffs_epfile		*epfiles;
पूर्ण;


काष्ठा f_fs_opts अणु
	काष्ठा usb_function_instance	func_inst;
	काष्ठा ffs_dev			*dev;
	अचिन्हित			refcnt;
	bool				no_configfs;
पूर्ण;

अटल अंतरभूत काष्ठा f_fs_opts *to_f_fs_opts(काष्ठा usb_function_instance *fi)
अणु
	वापस container_of(fi, काष्ठा f_fs_opts, func_inst);
पूर्ण

#पूर्ण_अगर /* U_FFS_H */
