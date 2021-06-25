<शैली गुरु>
/*
 * loop.h
 *
 * Written by Theoकरोre Ts'o, 3/29/93.
 *
 * Copyright 1993 by Theoकरोre Ts'o.  Redistribution of this file is
 * permitted under the GNU General Public License.
 */
#अगर_अघोषित _LINUX_LOOP_H
#घोषणा _LINUX_LOOP_H

#समावेश <linux/bपन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <uapi/linux/loop.h>

/* Possible states of device */
क्रमागत अणु
	Lo_unbound,
	Lo_bound,
	Lo_runकरोwn,
	Lo_deleting,
पूर्ण;

काष्ठा loop_func_table;

काष्ठा loop_device अणु
	पूर्णांक		lo_number;
	atomic_t	lo_refcnt;
	loff_t		lo_offset;
	loff_t		lo_sizelimit;
	पूर्णांक		lo_flags;
	पूर्णांक		(*transfer)(काष्ठा loop_device *, पूर्णांक cmd,
				    काष्ठा page *raw_page, अचिन्हित raw_off,
				    काष्ठा page *loop_page, अचिन्हित loop_off,
				    पूर्णांक size, sector_t real_block);
	अक्षर		lo_file_name[LO_NAME_SIZE];
	अक्षर		lo_crypt_name[LO_NAME_SIZE];
	अक्षर		lo_encrypt_key[LO_KEY_SIZE];
	पूर्णांक		lo_encrypt_key_size;
	काष्ठा loop_func_table *lo_encryption;
	__u32           lo_init[2];
	kuid_t		lo_key_owner;	/* Who set the key */
	पूर्णांक		(*ioctl)(काष्ठा loop_device *, पूर्णांक cmd, 
				 अचिन्हित दीर्घ arg); 

	काष्ठा file *	lo_backing_file;
	काष्ठा block_device *lo_device;
	व्योम		*key_data; 

	gfp_t		old_gfp_mask;

	spinlock_t		lo_lock;
	पूर्णांक			lo_state;
	काष्ठा kthपढ़ो_worker	worker;
	काष्ठा task_काष्ठा	*worker_task;
	bool			use_dio;
	bool			sysfs_inited;

	काष्ठा request_queue	*lo_queue;
	काष्ठा blk_mq_tag_set	tag_set;
	काष्ठा gendisk		*lo_disk;
	काष्ठा mutex		lo_mutex;
पूर्ण;

काष्ठा loop_cmd अणु
	काष्ठा kthपढ़ो_work work;
	bool use_aio; /* use AIO पूर्णांकerface to handle I/O */
	atomic_t ref; /* only क्रम aio */
	दीर्घ ret;
	काष्ठा kiocb iocb;
	काष्ठा bio_vec *bvec;
	काष्ठा cgroup_subsys_state *css;
पूर्ण;

/* Support क्रम loadable transfer modules */
काष्ठा loop_func_table अणु
	पूर्णांक number;	/* filter type */ 
	पूर्णांक (*transfer)(काष्ठा loop_device *lo, पूर्णांक cmd,
			काष्ठा page *raw_page, अचिन्हित raw_off,
			काष्ठा page *loop_page, अचिन्हित loop_off,
			पूर्णांक size, sector_t real_block);
	पूर्णांक (*init)(काष्ठा loop_device *, स्थिर काष्ठा loop_info64 *); 
	/* release is called from loop_unरेजिस्टर_transfer or clr_fd */
	पूर्णांक (*release)(काष्ठा loop_device *); 
	पूर्णांक (*ioctl)(काष्ठा loop_device *, पूर्णांक cmd, अचिन्हित दीर्घ arg);
	काष्ठा module *owner;
पूर्ण; 

पूर्णांक loop_रेजिस्टर_transfer(काष्ठा loop_func_table *funcs);
पूर्णांक loop_unरेजिस्टर_transfer(पूर्णांक number); 

#पूर्ण_अगर
