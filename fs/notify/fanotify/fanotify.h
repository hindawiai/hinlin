<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/fsnotअगरy_backend.h>
#समावेश <linux/path.h>
#समावेश <linux/slab.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/hashtable.h>

बाह्य काष्ठा kmem_cache *fanotअगरy_mark_cache;
बाह्य काष्ठा kmem_cache *fanotअगरy_fid_event_cachep;
बाह्य काष्ठा kmem_cache *fanotअगरy_path_event_cachep;
बाह्य काष्ठा kmem_cache *fanotअगरy_perm_event_cachep;

/* Possible states of the permission event */
क्रमागत अणु
	FAN_EVENT_INIT,
	FAN_EVENT_REPORTED,
	FAN_EVENT_ANSWERED,
	FAN_EVENT_CANCELED,
पूर्ण;

/*
 * 3 dwords are sufficient क्रम most local fs (64bit ino, 32bit generation).
 * fh buf should be dword aligned. On 64bit arch, the ext_buf poपूर्णांकer is
 * stored in either the first or last 2 dwords.
 */
#घोषणा FANOTIFY_INLINE_FH_LEN	(3 << 2)
#घोषणा FANOTIFY_FH_HDR_LEN	दुरत्व(काष्ठा fanotअगरy_fh, buf)

/* Fixed size काष्ठा क्रम file handle */
काष्ठा fanotअगरy_fh अणु
	u8 type;
	u8 len;
#घोषणा FANOTIFY_FH_FLAG_EXT_BUF 1
	u8 flags;
	u8 pad;
	अचिन्हित अक्षर buf[];
पूर्ण __aligned(4);

/* Variable size काष्ठा क्रम dir file handle + child file handle + name */
काष्ठा fanotअगरy_info अणु
	/* size of dir_fh/file_fh including fanotअगरy_fh hdr size */
	u8 dir_fh_totlen;
	u8 file_fh_totlen;
	u8 name_len;
	u8 pad;
	अचिन्हित अक्षर buf[];
	/*
	 * (काष्ठा fanotअगरy_fh) dir_fh starts at buf[0]
	 * (optional) file_fh starts at buf[dir_fh_totlen]
	 * name starts at buf[dir_fh_totlen + file_fh_totlen]
	 */
पूर्ण __aligned(4);

अटल अंतरभूत bool fanotअगरy_fh_has_ext_buf(काष्ठा fanotअगरy_fh *fh)
अणु
	वापस (fh->flags & FANOTIFY_FH_FLAG_EXT_BUF);
पूर्ण

अटल अंतरभूत अक्षर **fanotअगरy_fh_ext_buf_ptr(काष्ठा fanotअगरy_fh *fh)
अणु
	BUILD_BUG_ON(FANOTIFY_FH_HDR_LEN % 4);
	BUILD_BUG_ON(__alignof__(अक्षर *) - 4 + माप(अक्षर *) >
		     FANOTIFY_INLINE_FH_LEN);
	वापस (अक्षर **)ALIGN((अचिन्हित दीर्घ)(fh->buf), __alignof__(अक्षर *));
पूर्ण

अटल अंतरभूत व्योम *fanotअगरy_fh_ext_buf(काष्ठा fanotअगरy_fh *fh)
अणु
	वापस *fanotअगरy_fh_ext_buf_ptr(fh);
पूर्ण

अटल अंतरभूत व्योम *fanotअगरy_fh_buf(काष्ठा fanotअगरy_fh *fh)
अणु
	वापस fanotअगरy_fh_has_ext_buf(fh) ? fanotअगरy_fh_ext_buf(fh) : fh->buf;
पूर्ण

अटल अंतरभूत पूर्णांक fanotअगरy_info_dir_fh_len(काष्ठा fanotअगरy_info *info)
अणु
	अगर (!info->dir_fh_totlen ||
	    WARN_ON_ONCE(info->dir_fh_totlen < FANOTIFY_FH_HDR_LEN))
		वापस 0;

	वापस info->dir_fh_totlen - FANOTIFY_FH_HDR_LEN;
पूर्ण

अटल अंतरभूत काष्ठा fanotअगरy_fh *fanotअगरy_info_dir_fh(काष्ठा fanotअगरy_info *info)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा fanotअगरy_info, buf) % 4);

	वापस (काष्ठा fanotअगरy_fh *)info->buf;
पूर्ण

अटल अंतरभूत पूर्णांक fanotअगरy_info_file_fh_len(काष्ठा fanotअगरy_info *info)
अणु
	अगर (!info->file_fh_totlen ||
	    WARN_ON_ONCE(info->file_fh_totlen < FANOTIFY_FH_HDR_LEN))
		वापस 0;

	वापस info->file_fh_totlen - FANOTIFY_FH_HDR_LEN;
पूर्ण

अटल अंतरभूत काष्ठा fanotअगरy_fh *fanotअगरy_info_file_fh(काष्ठा fanotअगरy_info *info)
अणु
	वापस (काष्ठा fanotअगरy_fh *)(info->buf + info->dir_fh_totlen);
पूर्ण

अटल अंतरभूत स्थिर अक्षर *fanotअगरy_info_name(काष्ठा fanotअगरy_info *info)
अणु
	वापस info->buf + info->dir_fh_totlen + info->file_fh_totlen;
पूर्ण

अटल अंतरभूत व्योम fanotअगरy_info_init(काष्ठा fanotअगरy_info *info)
अणु
	info->dir_fh_totlen = 0;
	info->file_fh_totlen = 0;
	info->name_len = 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक fanotअगरy_info_len(काष्ठा fanotअगरy_info *info)
अणु
	वापस info->dir_fh_totlen + info->file_fh_totlen + info->name_len;
पूर्ण

अटल अंतरभूत व्योम fanotअगरy_info_copy_name(काष्ठा fanotअगरy_info *info,
					   स्थिर काष्ठा qstr *name)
अणु
	info->name_len = name->len;
	म_नकल(info->buf + info->dir_fh_totlen + info->file_fh_totlen,
	       name->name);
पूर्ण

/*
 * Common काष्ठाure क्रम fanotअगरy events. Concrete काष्ठाs are allocated in
 * fanotअगरy_handle_event() and मुक्तd when the inक्रमmation is retrieved by
 * userspace. The type of event determines how it was allocated, how it will
 * be मुक्तd and which concrete काष्ठा it may be cast to.
 */
क्रमागत fanotअगरy_event_type अणु
	FANOTIFY_EVENT_TYPE_FID, /* fixed length */
	FANOTIFY_EVENT_TYPE_FID_NAME, /* variable length */
	FANOTIFY_EVENT_TYPE_PATH,
	FANOTIFY_EVENT_TYPE_PATH_PERM,
	FANOTIFY_EVENT_TYPE_OVERFLOW, /* काष्ठा fanotअगरy_event */
	__FANOTIFY_EVENT_TYPE_NUM
पूर्ण;

#घोषणा FANOTIFY_EVENT_TYPE_BITS \
	(ilog2(__FANOTIFY_EVENT_TYPE_NUM - 1) + 1)
#घोषणा FANOTIFY_EVENT_HASH_BITS \
	(32 - FANOTIFY_EVENT_TYPE_BITS)

काष्ठा fanotअगरy_event अणु
	काष्ठा fsnotअगरy_event fse;
	काष्ठा hlist_node merge_list;	/* List क्रम hashed merge */
	u32 mask;
	काष्ठा अणु
		अचिन्हित पूर्णांक type : FANOTIFY_EVENT_TYPE_BITS;
		अचिन्हित पूर्णांक hash : FANOTIFY_EVENT_HASH_BITS;
	पूर्ण;
	काष्ठा pid *pid;
पूर्ण;

अटल अंतरभूत व्योम fanotअगरy_init_event(काष्ठा fanotअगरy_event *event,
				       अचिन्हित पूर्णांक hash, u32 mask)
अणु
	fsnotअगरy_init_event(&event->fse);
	INIT_HLIST_NODE(&event->merge_list);
	event->hash = hash;
	event->mask = mask;
	event->pid = शून्य;
पूर्ण

काष्ठा fanotअगरy_fid_event अणु
	काष्ठा fanotअगरy_event fae;
	__kernel_fsid_t fsid;
	काष्ठा fanotअगरy_fh object_fh;
	/* Reserve space in object_fh.buf[] - access with fanotअगरy_fh_buf() */
	अचिन्हित अक्षर _अंतरभूत_fh_buf[FANOTIFY_INLINE_FH_LEN];
पूर्ण;

अटल अंतरभूत काष्ठा fanotअगरy_fid_event *
FANOTIFY_FE(काष्ठा fanotअगरy_event *event)
अणु
	वापस container_of(event, काष्ठा fanotअगरy_fid_event, fae);
पूर्ण

काष्ठा fanotअगरy_name_event अणु
	काष्ठा fanotअगरy_event fae;
	__kernel_fsid_t fsid;
	काष्ठा fanotअगरy_info info;
पूर्ण;

अटल अंतरभूत काष्ठा fanotअगरy_name_event *
FANOTIFY_NE(काष्ठा fanotअगरy_event *event)
अणु
	वापस container_of(event, काष्ठा fanotअगरy_name_event, fae);
पूर्ण

अटल अंतरभूत __kernel_fsid_t *fanotअगरy_event_fsid(काष्ठा fanotअगरy_event *event)
अणु
	अगर (event->type == FANOTIFY_EVENT_TYPE_FID)
		वापस &FANOTIFY_FE(event)->fsid;
	अन्यथा अगर (event->type == FANOTIFY_EVENT_TYPE_FID_NAME)
		वापस &FANOTIFY_NE(event)->fsid;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा fanotअगरy_fh *fanotअगरy_event_object_fh(
						काष्ठा fanotअगरy_event *event)
अणु
	अगर (event->type == FANOTIFY_EVENT_TYPE_FID)
		वापस &FANOTIFY_FE(event)->object_fh;
	अन्यथा अगर (event->type == FANOTIFY_EVENT_TYPE_FID_NAME)
		वापस fanotअगरy_info_file_fh(&FANOTIFY_NE(event)->info);
	अन्यथा
		वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा fanotअगरy_info *fanotअगरy_event_info(
						काष्ठा fanotअगरy_event *event)
अणु
	अगर (event->type == FANOTIFY_EVENT_TYPE_FID_NAME)
		वापस &FANOTIFY_NE(event)->info;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल अंतरभूत पूर्णांक fanotअगरy_event_object_fh_len(काष्ठा fanotअगरy_event *event)
अणु
	काष्ठा fanotअगरy_info *info = fanotअगरy_event_info(event);
	काष्ठा fanotअगरy_fh *fh = fanotअगरy_event_object_fh(event);

	अगर (info)
		वापस info->file_fh_totlen ? fh->len : 0;
	अन्यथा
		वापस fh ? fh->len : 0;
पूर्ण

अटल अंतरभूत पूर्णांक fanotअगरy_event_dir_fh_len(काष्ठा fanotअगरy_event *event)
अणु
	काष्ठा fanotअगरy_info *info = fanotअगरy_event_info(event);

	वापस info ? fanotअगरy_info_dir_fh_len(info) : 0;
पूर्ण

काष्ठा fanotअगरy_path_event अणु
	काष्ठा fanotअगरy_event fae;
	काष्ठा path path;
पूर्ण;

अटल अंतरभूत काष्ठा fanotअगरy_path_event *
FANOTIFY_PE(काष्ठा fanotअगरy_event *event)
अणु
	वापस container_of(event, काष्ठा fanotअगरy_path_event, fae);
पूर्ण

/*
 * Structure क्रम permission fanotअगरy events. It माला_लो allocated and मुक्तd in
 * fanotअगरy_handle_event() since we रुको there क्रम user response. When the
 * inक्रमmation is retrieved by userspace the काष्ठाure is moved from
 * group->notअगरication_list to group->fanotअगरy_data.access_list to रुको क्रम
 * user response.
 */
काष्ठा fanotअगरy_perm_event अणु
	काष्ठा fanotअगरy_event fae;
	काष्ठा path path;
	अचिन्हित लघु response;	/* userspace answer to the event */
	अचिन्हित लघु state;		/* state of the event */
	पूर्णांक fd;		/* fd we passed to userspace क्रम this event */
पूर्ण;

अटल अंतरभूत काष्ठा fanotअगरy_perm_event *
FANOTIFY_PERM(काष्ठा fanotअगरy_event *event)
अणु
	वापस container_of(event, काष्ठा fanotअगरy_perm_event, fae);
पूर्ण

अटल अंतरभूत bool fanotअगरy_is_perm_event(u32 mask)
अणु
	वापस IS_ENABLED(CONFIG_FANOTIFY_ACCESS_PERMISSIONS) &&
		mask & FANOTIFY_PERM_EVENTS;
पूर्ण

अटल अंतरभूत काष्ठा fanotअगरy_event *FANOTIFY_E(काष्ठा fsnotअगरy_event *fse)
अणु
	वापस container_of(fse, काष्ठा fanotअगरy_event, fse);
पूर्ण

अटल अंतरभूत bool fanotअगरy_event_has_path(काष्ठा fanotअगरy_event *event)
अणु
	वापस event->type == FANOTIFY_EVENT_TYPE_PATH ||
		event->type == FANOTIFY_EVENT_TYPE_PATH_PERM;
पूर्ण

अटल अंतरभूत काष्ठा path *fanotअगरy_event_path(काष्ठा fanotअगरy_event *event)
अणु
	अगर (event->type == FANOTIFY_EVENT_TYPE_PATH)
		वापस &FANOTIFY_PE(event)->path;
	अन्यथा अगर (event->type == FANOTIFY_EVENT_TYPE_PATH_PERM)
		वापस &FANOTIFY_PERM(event)->path;
	अन्यथा
		वापस शून्य;
पूर्ण

/*
 * Use 128 size hash table to speed up events merge.
 */
#घोषणा FANOTIFY_HTABLE_BITS	(7)
#घोषणा FANOTIFY_HTABLE_SIZE	(1 << FANOTIFY_HTABLE_BITS)
#घोषणा FANOTIFY_HTABLE_MASK	(FANOTIFY_HTABLE_SIZE - 1)

/*
 * Permission events and overflow event करो not get merged - करोn't hash them.
 */
अटल अंतरभूत bool fanotअगरy_is_hashed_event(u32 mask)
अणु
	वापस !fanotअगरy_is_perm_event(mask) && !(mask & FS_Q_OVERFLOW);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक fanotअगरy_event_hash_bucket(
						काष्ठा fsnotअगरy_group *group,
						काष्ठा fanotअगरy_event *event)
अणु
	वापस event->hash & FANOTIFY_HTABLE_MASK;
पूर्ण
