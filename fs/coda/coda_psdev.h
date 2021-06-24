<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __CODA_PSDEV_H
#घोषणा __CODA_PSDEV_H

#समावेश <linux/backing-dev.h>
#समावेश <linux/magic.h>
#समावेश <linux/mutex.h>

#घोषणा CODA_PSDEV_MAJOR 67
#घोषणा MAX_CODADEVS  5	   /* how many करो we allow */

काष्ठा kstatfs;

/* messages between coda fileप्रणाली in kernel and Venus */
काष्ठा upc_req अणु
	काष्ठा list_head	uc_chain;
	caddr_t			uc_data;
	u_लघु			uc_flags;
	u_लघु			uc_inSize;  /* Size is at most 5000 bytes */
	u_लघु			uc_outSize;
	u_लघु			uc_opcode;  /* copied from data to save lookup */
	पूर्णांक			uc_unique;
	रुको_queue_head_t	uc_sleep;   /* process' रुको queue */
पूर्ण;

#घोषणा CODA_REQ_ASYNC  0x1
#घोषणा CODA_REQ_READ   0x2
#घोषणा CODA_REQ_WRITE  0x4
#घोषणा CODA_REQ_ABORT  0x8

/* communication pending/processing queues */
काष्ठा venus_comm अणु
	u_दीर्घ		    vc_seq;
	रुको_queue_head_t   vc_रुकोq; /* Venus रुको queue */
	काष्ठा list_head    vc_pending;
	काष्ठा list_head    vc_processing;
	पूर्णांक                 vc_inuse;
	काष्ठा super_block *vc_sb;
	काष्ठा mutex	    vc_mutex;
पूर्ण;

अटल अंतरभूत काष्ठा venus_comm *coda_vcp(काष्ठा super_block *sb)
अणु
	वापस (काष्ठा venus_comm *)((sb)->s_fs_info);
पूर्ण

/* upcalls */
पूर्णांक venus_rootfid(काष्ठा super_block *sb, काष्ठा CodaFid *fidp);
पूर्णांक venus_getattr(काष्ठा super_block *sb, काष्ठा CodaFid *fid,
		  काष्ठा coda_vattr *attr);
पूर्णांक venus_setattr(काष्ठा super_block *, काष्ठा CodaFid *, काष्ठा coda_vattr *);
पूर्णांक venus_lookup(काष्ठा super_block *sb, काष्ठा CodaFid *fid,
		 स्थिर अक्षर *name, पूर्णांक length, पूर्णांक *type,
		 काष्ठा CodaFid *resfid);
पूर्णांक venus_बंद(काष्ठा super_block *sb, काष्ठा CodaFid *fid, पूर्णांक flags,
		kuid_t uid);
पूर्णांक venus_खोलो(काष्ठा super_block *sb, काष्ठा CodaFid *fid, पूर्णांक flags,
	       काष्ठा file **f);
पूर्णांक venus_सूची_गढ़ो(काष्ठा super_block *sb, काष्ठा CodaFid *dirfid,
		स्थिर अक्षर *name, पूर्णांक length,
		काष्ठा CodaFid *newfid, काष्ठा coda_vattr *attrs);
पूर्णांक venus_create(काष्ठा super_block *sb, काष्ठा CodaFid *dirfid,
		 स्थिर अक्षर *name, पूर्णांक length, पूर्णांक excl, पूर्णांक mode,
		 काष्ठा CodaFid *newfid, काष्ठा coda_vattr *attrs);
पूर्णांक venus_सूची_हटाओ(काष्ठा super_block *sb, काष्ठा CodaFid *dirfid,
		स्थिर अक्षर *name, पूर्णांक length);
पूर्णांक venus_हटाओ(काष्ठा super_block *sb, काष्ठा CodaFid *dirfid,
		 स्थिर अक्षर *name, पूर्णांक length);
पूर्णांक venus_पढ़ोlink(काष्ठा super_block *sb, काष्ठा CodaFid *fid,
		   अक्षर *buffer, पूर्णांक *length);
पूर्णांक venus_नाम(काष्ठा super_block *sb, काष्ठा CodaFid *new_fid,
		 काष्ठा CodaFid *old_fid, माप_प्रकार old_length,
		 माप_प्रकार new_length, स्थिर अक्षर *old_name,
		 स्थिर अक्षर *new_name);
पूर्णांक venus_link(काष्ठा super_block *sb, काष्ठा CodaFid *fid,
		  काष्ठा CodaFid *dirfid, स्थिर अक्षर *name, पूर्णांक len );
पूर्णांक venus_symlink(काष्ठा super_block *sb, काष्ठा CodaFid *fid,
		  स्थिर अक्षर *name, पूर्णांक len, स्थिर अक्षर *symname, पूर्णांक symlen);
पूर्णांक venus_access(काष्ठा super_block *sb, काष्ठा CodaFid *fid, पूर्णांक mask);
पूर्णांक venus_pioctl(काष्ठा super_block *sb, काष्ठा CodaFid *fid,
		 अचिन्हित पूर्णांक cmd, काष्ठा PioctlData *data);
पूर्णांक coda_करोwncall(काष्ठा venus_comm *vcp, पूर्णांक opcode, जोड़ outputArgs *out,
		  माप_प्रकार nbytes);
पूर्णांक venus_fsync(काष्ठा super_block *sb, काष्ठा CodaFid *fid);
पूर्णांक venus_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *sfs);
पूर्णांक venus_access_पूर्णांकent(काष्ठा super_block *sb, काष्ठा CodaFid *fid,
			bool *access_पूर्णांकent_supported,
			माप_प्रकार count, loff_t ppos, पूर्णांक type);

/*
 * Statistics
 */

बाह्य काष्ठा venus_comm coda_comms[];
#पूर्ण_अगर
