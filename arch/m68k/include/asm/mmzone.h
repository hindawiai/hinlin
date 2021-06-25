<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_M68K_MMZONE_H_
#घोषणा _ASM_M68K_MMZONE_H_

बाह्य pg_data_t pg_data_map[];

#घोषणा NODE_DATA(nid)		(&pg_data_map[nid])
#घोषणा NODE_MEM_MAP(nid)	(NODE_DATA(nid)->node_mem_map)

#पूर्ण_अगर /* _ASM_M68K_MMZONE_H_ */
