<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित _ASM_SN_KLसूची_H
#घोषणा _ASM_SN_KLसूची_H

#घोषणा KLसूची_MAGIC		0x434d5f53505f5357

#घोषणा KLसूची_OFF_MAGIC			0x00
#घोषणा KLसूची_OFF_OFFSET		0x08
#घोषणा KLसूची_OFF_POINTER		0x10
#घोषणा KLसूची_OFF_SIZE			0x18
#घोषणा KLसूची_OFF_COUNT			0x20
#घोषणा KLसूची_OFF_STRIDE		0x28

#घोषणा KLसूची_ENT_SIZE			0x40
#घोषणा KLसूची_MAX_ENTRIES		(0x400 / 0x40)

#अगर_अघोषित __ASSEMBLY__
प्रकार काष्ठा kldir_ent_s अणु
	u64		magic;		/* Indicates validity of entry	    */
	off_t		offset;		/* Offset from start of node space  */
	अचिन्हित दीर्घ	poपूर्णांकer;	/* Poपूर्णांकer to area in some हालs    */
	माप_प्रकार		size;		/* Size in bytes		    */
	u64		count;		/* Repeat count अगर array, 1 अगर not  */
	माप_प्रकार		stride;		/* Stride अगर array, 0 अगर not	    */
	अक्षर		rsvd[16];	/* Pad entry to 0x40 bytes	    */
	/* NOTE: These 16 bytes are used in the Partition KLसूची
	   entry to store partition info. Refer to klpart.h क्रम this. */
पूर्ण kldir_ent_t;
#पूर्ण_अगर /* !__ASSEMBLY__ */

#अगर_घोषित CONFIG_SGI_IP27
#समावेश <यंत्र/sn/sn0/klसूची.स>
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_SN_KLसूची_H */
