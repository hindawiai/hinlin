<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ALPHA_GCT_H
#घोषणा __ALPHA_GCT_H

प्रकार u64 gct_id;
प्रकार u64 gct6_handle;

प्रकार काष्ठा __gct6_node अणु
	u8 type;	
	u8 subtype;
	u16 size;
	u32 hd_extension;
	gct6_handle owner;
	gct6_handle active_user;
	gct_id id;
	u64 flags;
	u16 rev;
	u16 change_counter;
	u16 max_child;
	u16 reserved1;
	gct6_handle saved_owner;
	gct6_handle affinity;
	gct6_handle parent;
	gct6_handle next;
	gct6_handle prev;
	gct6_handle child;
	u64 fw_flags;
	u64 os_usage;
	u64 fru_id;
	u32 checksum;
	u32 magic;	/* 'GLXY' */
पूर्ण gct6_node;

प्रकार काष्ठा अणु
	u8 type;	
	u8 subtype;
	व्योम (*callout)(gct6_node *);
पूर्ण gct6_search_काष्ठा;

#घोषणा GCT_NODE_MAGIC	  0x59584c47	/* 'GLXY' */

/* 
 * node types 
 */
#घोषणा GCT_TYPE_HOSE			0x0E

/*
 * node subtypes
 */
#घोषणा GCT_SUBTYPE_IO_PORT_MODULE	0x2C

#घोषणा GCT_NODE_PTR(off) ((gct6_node *)((अक्षर *)hwrpb + 		\
					 hwrpb->frut_offset + 		\
					 (gct6_handle)(off)))		\

पूर्णांक gct6_find_nodes(gct6_node *, gct6_search_काष्ठा *);

#पूर्ण_अगर /* __ALPHA_GCT_H */

