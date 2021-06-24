<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __BLK_शून्य_BLK_H
#घोषणा __BLK_शून्य_BLK_H

#अघोषित pr_fmt
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/blkdev.h>
#समावेश <linux/slab.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/hrसमयr.h>
#समावेश <linux/configfs.h>
#समावेश <linux/badblocks.h>
#समावेश <linux/fault-inject.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mutex.h>

काष्ठा nullb_cmd अणु
	काष्ठा request *rq;
	काष्ठा bio *bio;
	अचिन्हित पूर्णांक tag;
	blk_status_t error;
	काष्ठा nullb_queue *nq;
	काष्ठा hrसमयr समयr;
	bool fake_समयout;
पूर्ण;

काष्ठा nullb_queue अणु
	अचिन्हित दीर्घ *tag_map;
	रुको_queue_head_t रुको;
	अचिन्हित पूर्णांक queue_depth;
	काष्ठा nullb_device *dev;
	अचिन्हित पूर्णांक requeue_selection;

	काष्ठा nullb_cmd *cmds;
पूर्ण;

काष्ठा nullb_zone अणु
	/*
	 * Zone lock to prevent concurrent modअगरication of a zone ग_लिखो
	 * poपूर्णांकer position and condition: with memory backing, a ग_लिखो
	 * command execution may sleep on memory allocation. For this हाल,
	 * use mutex as the zone lock. Otherwise, use the spinlock क्रम
	 * locking the zone.
	 */
	जोड़ अणु
		spinlock_t spinlock;
		काष्ठा mutex mutex;
	पूर्ण;
	क्रमागत blk_zone_type type;
	क्रमागत blk_zone_cond cond;
	sector_t start;
	sector_t wp;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक capacity;
पूर्ण;

काष्ठा nullb_device अणु
	काष्ठा nullb *nullb;
	काष्ठा config_item item;
	काष्ठा radix_tree_root data; /* data stored in the disk */
	काष्ठा radix_tree_root cache; /* disk cache data */
	अचिन्हित दीर्घ flags; /* device flags */
	अचिन्हित पूर्णांक curr_cache;
	काष्ठा badblocks badblocks;

	अचिन्हित पूर्णांक nr_zones;
	अचिन्हित पूर्णांक nr_zones_imp_खोलो;
	अचिन्हित पूर्णांक nr_zones_exp_खोलो;
	अचिन्हित पूर्णांक nr_zones_बंदd;
	अचिन्हित पूर्णांक imp_बंद_zone_no;
	काष्ठा nullb_zone *zones;
	sector_t zone_size_sects;
	bool need_zone_res_mgmt;
	spinlock_t zone_res_lock;

	अचिन्हित दीर्घ size; /* device size in MB */
	अचिन्हित दीर्घ completion_nsec; /* समय in ns to complete a request */
	अचिन्हित दीर्घ cache_size; /* disk cache size in MB */
	अचिन्हित दीर्घ zone_size; /* zone size in MB अगर device is zoned */
	अचिन्हित दीर्घ zone_capacity; /* zone capacity in MB अगर device is zoned */
	अचिन्हित पूर्णांक zone_nr_conv; /* number of conventional zones */
	अचिन्हित पूर्णांक zone_max_खोलो; /* max number of खोलो zones */
	अचिन्हित पूर्णांक zone_max_active; /* max number of active zones */
	अचिन्हित पूर्णांक submit_queues; /* number of submission queues */
	अचिन्हित पूर्णांक home_node; /* home node क्रम the device */
	अचिन्हित पूर्णांक queue_mode; /* block पूर्णांकerface */
	अचिन्हित पूर्णांक blocksize; /* block size */
	अचिन्हित पूर्णांक max_sectors; /* Max sectors per command */
	अचिन्हित पूर्णांक irqmode; /* IRQ completion handler */
	अचिन्हित पूर्णांक hw_queue_depth; /* queue depth */
	अचिन्हित पूर्णांक index; /* index of the disk, only valid with a disk */
	अचिन्हित पूर्णांक mbps; /* Bandwidth throttle cap (in MB/s) */
	bool blocking; /* blocking blk-mq device */
	bool use_per_node_hctx; /* use per-node allocation क्रम hardware context */
	bool घातer; /* घातer on/off the device */
	bool memory_backed; /* अगर data is stored in memory */
	bool discard; /* अगर support discard */
	bool zoned; /* अगर device is zoned */
	bool virt_boundary; /* भव boundary on/off क्रम the device */
पूर्ण;

काष्ठा nullb अणु
	काष्ठा nullb_device *dev;
	काष्ठा list_head list;
	अचिन्हित पूर्णांक index;
	काष्ठा request_queue *q;
	काष्ठा gendisk *disk;
	काष्ठा blk_mq_tag_set *tag_set;
	काष्ठा blk_mq_tag_set __tag_set;
	अचिन्हित पूर्णांक queue_depth;
	atomic_दीर्घ_t cur_bytes;
	काष्ठा hrसमयr bw_समयr;
	अचिन्हित दीर्घ cache_flush_pos;
	spinlock_t lock;

	काष्ठा nullb_queue *queues;
	अचिन्हित पूर्णांक nr_queues;
	अक्षर disk_name[DISK_NAME_LEN];
पूर्ण;

blk_status_t null_handle_discard(काष्ठा nullb_device *dev, sector_t sector,
				 sector_t nr_sectors);
blk_status_t null_process_cmd(काष्ठा nullb_cmd *cmd,
			      क्रमागत req_opf op, sector_t sector,
			      अचिन्हित पूर्णांक nr_sectors);

#अगर_घोषित CONFIG_BLK_DEV_ZONED
पूर्णांक null_init_zoned_dev(काष्ठा nullb_device *dev, काष्ठा request_queue *q);
पूर्णांक null_रेजिस्टर_zoned_dev(काष्ठा nullb *nullb);
व्योम null_मुक्त_zoned_dev(काष्ठा nullb_device *dev);
पूर्णांक null_report_zones(काष्ठा gendisk *disk, sector_t sector,
		      अचिन्हित पूर्णांक nr_zones, report_zones_cb cb, व्योम *data);
blk_status_t null_process_zoned_cmd(काष्ठा nullb_cmd *cmd,
				    क्रमागत req_opf op, sector_t sector,
				    sector_t nr_sectors);
माप_प्रकार null_zone_valid_पढ़ो_len(काष्ठा nullb *nullb,
				sector_t sector, अचिन्हित पूर्णांक len);
#अन्यथा
अटल अंतरभूत पूर्णांक null_init_zoned_dev(काष्ठा nullb_device *dev,
				      काष्ठा request_queue *q)
अणु
	pr_err("CONFIG_BLK_DEV_ZONED not enabled\n");
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक null_रेजिस्टर_zoned_dev(काष्ठा nullb *nullb)
अणु
	वापस -ENODEV;
पूर्ण
अटल अंतरभूत व्योम null_मुक्त_zoned_dev(काष्ठा nullb_device *dev) अणुपूर्ण
अटल अंतरभूत blk_status_t null_process_zoned_cmd(काष्ठा nullb_cmd *cmd,
			क्रमागत req_opf op, sector_t sector, sector_t nr_sectors)
अणु
	वापस BLK_STS_NOTSUPP;
पूर्ण
अटल अंतरभूत माप_प्रकार null_zone_valid_पढ़ो_len(काष्ठा nullb *nullb,
					      sector_t sector,
					      अचिन्हित पूर्णांक len)
अणु
	वापस len;
पूर्ण
#घोषणा null_report_zones	शून्य
#पूर्ण_अगर /* CONFIG_BLK_DEV_ZONED */
#पूर्ण_अगर /* __शून्य_BLK_H */
