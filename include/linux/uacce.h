<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _LINUX_UACCE_H
#घोषणा _LINUX_UACCE_H

#समावेश <linux/cdev.h>
#समावेश <uapi/misc/uacce/uacce.h>

#घोषणा UACCE_NAME		"uacce"
#घोषणा UACCE_MAX_REGION	2
#घोषणा UACCE_MAX_NAME_SIZE	64

काष्ठा uacce_queue;
काष्ठा uacce_device;

/**
 * काष्ठा uacce_qfile_region - काष्ठाure of queue file region
 * @type: type of the region
 */
काष्ठा uacce_qfile_region अणु
	क्रमागत uacce_qfrt type;
पूर्ण;

/**
 * काष्ठा uacce_ops - uacce device operations
 * @get_available_instances:  get available instances left of the device
 * @get_queue: get a queue from the device
 * @put_queue: मुक्त a queue to the device
 * @start_queue: make the queue start work after get_queue
 * @stop_queue: make the queue stop work beक्रमe put_queue
 * @is_q_updated: check whether the task is finished
 * @mmap: mmap addresses of queue to user space
 * @ioctl: ioctl क्रम user space users of the queue
 */
काष्ठा uacce_ops अणु
	पूर्णांक (*get_available_instances)(काष्ठा uacce_device *uacce);
	पूर्णांक (*get_queue)(काष्ठा uacce_device *uacce, अचिन्हित दीर्घ arg,
			 काष्ठा uacce_queue *q);
	व्योम (*put_queue)(काष्ठा uacce_queue *q);
	पूर्णांक (*start_queue)(काष्ठा uacce_queue *q);
	व्योम (*stop_queue)(काष्ठा uacce_queue *q);
	पूर्णांक (*is_q_updated)(काष्ठा uacce_queue *q);
	पूर्णांक (*mmap)(काष्ठा uacce_queue *q, काष्ठा vm_area_काष्ठा *vma,
		    काष्ठा uacce_qfile_region *qfr);
	दीर्घ (*ioctl)(काष्ठा uacce_queue *q, अचिन्हित पूर्णांक cmd,
		      अचिन्हित दीर्घ arg);
पूर्ण;

/**
 * काष्ठा uacce_पूर्णांकerface - पूर्णांकerface required क्रम uacce_रेजिस्टर()
 * @name: the uacce device name.  Will show up in sysfs
 * @flags: uacce device attributes
 * @ops: poपूर्णांकer to the काष्ठा uacce_ops
 */
काष्ठा uacce_पूर्णांकerface अणु
	अक्षर name[UACCE_MAX_NAME_SIZE];
	अचिन्हित पूर्णांक flags;
	स्थिर काष्ठा uacce_ops *ops;
पूर्ण;

क्रमागत uacce_q_state अणु
	UACCE_Q_ZOMBIE = 0,
	UACCE_Q_INIT,
	UACCE_Q_STARTED,
पूर्ण;

/**
 * काष्ठा uacce_queue
 * @uacce: poपूर्णांकer to uacce
 * @priv: निजी poपूर्णांकer
 * @रुको: रुको queue head
 * @list: index पूर्णांकo uacce queues list
 * @qfrs: poपूर्णांकer of qfr regions
 * @state: queue state machine
 * @pasid: pasid associated to the mm
 * @handle: iommu_sva handle वापसed by iommu_sva_bind_device()
 */
काष्ठा uacce_queue अणु
	काष्ठा uacce_device *uacce;
	व्योम *priv;
	रुको_queue_head_t रुको;
	काष्ठा list_head list;
	काष्ठा uacce_qfile_region *qfrs[UACCE_MAX_REGION];
	क्रमागत uacce_q_state state;
	u32 pasid;
	काष्ठा iommu_sva *handle;
पूर्ण;

/**
 * काष्ठा uacce_device
 * @algs: supported algorithms
 * @api_ver: api version
 * @ops: poपूर्णांकer to the काष्ठा uacce_ops
 * @qf_pg_num: page numbers of the queue file regions
 * @parent: poपूर्णांकer to the parent device
 * @is_vf: whether भव function
 * @flags: uacce attributes
 * @dev_id: id of the uacce device
 * @cdev: cdev of the uacce
 * @dev: dev of the uacce
 * @priv: निजी poपूर्णांकer of the uacce
 * @queues: list of queues
 * @queues_lock: lock क्रम queues list
 * @inode: core vfs
 */
काष्ठा uacce_device अणु
	स्थिर अक्षर *algs;
	स्थिर अक्षर *api_ver;
	स्थिर काष्ठा uacce_ops *ops;
	अचिन्हित दीर्घ qf_pg_num[UACCE_MAX_REGION];
	काष्ठा device *parent;
	bool is_vf;
	u32 flags;
	u32 dev_id;
	काष्ठा cdev *cdev;
	काष्ठा device dev;
	व्योम *priv;
	काष्ठा list_head queues;
	काष्ठा mutex queues_lock;
	काष्ठा inode *inode;
पूर्ण;

#अगर IS_ENABLED(CONFIG_UACCE)

काष्ठा uacce_device *uacce_alloc(काष्ठा device *parent,
				 काष्ठा uacce_पूर्णांकerface *पूर्णांकerface);
पूर्णांक uacce_रेजिस्टर(काष्ठा uacce_device *uacce);
व्योम uacce_हटाओ(काष्ठा uacce_device *uacce);

#अन्यथा /* CONFIG_UACCE */

अटल अंतरभूत
काष्ठा uacce_device *uacce_alloc(काष्ठा device *parent,
				 काष्ठा uacce_पूर्णांकerface *पूर्णांकerface)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत पूर्णांक uacce_रेजिस्टर(काष्ठा uacce_device *uacce)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत व्योम uacce_हटाओ(काष्ठा uacce_device *uacce) अणुपूर्ण

#पूर्ण_अगर /* CONFIG_UACCE */

#पूर्ण_अगर /* _LINUX_UACCE_H */
