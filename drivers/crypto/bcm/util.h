<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2016 Broadcom
 */

#अगर_अघोषित _UTIL_H
#घोषणा _UTIL_H

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>

#समावेश "spu.h"

बाह्य पूर्णांक flow_debug_logging;
बाह्य पूर्णांक packet_debug_logging;
बाह्य पूर्णांक debug_logging_sleep;

#अगर_घोषित DEBUG
#घोषणा flow_log(...)	                \
	करो अणु	                              \
		अगर (flow_debug_logging) अणु	        \
			prपूर्णांकk(__VA_ARGS__);	          \
			अगर (debug_logging_sleep)	      \
				msleep(debug_logging_sleep);	\
		पूर्ण	                                \
	पूर्ण जबतक (0)
#घोषणा flow_dump(msg, var, var_len)	   \
	करो अणु	                                 \
		अगर (flow_debug_logging) अणु	           \
			prपूर्णांक_hex_dump(KERN_ALERT, msg, DUMP_PREFIX_NONE,  \
					16, 1, var, var_len, false); \
				अगर (debug_logging_sleep)	       \
					msleep(debug_logging_sleep);   \
		पूर्ण                                    \
	पूर्ण जबतक (0)

#घोषणा packet_log(...)               \
	करो अणु                                \
		अगर (packet_debug_logging) अणु       \
			prपूर्णांकk(__VA_ARGS__);            \
			अगर (debug_logging_sleep)        \
				msleep(debug_logging_sleep);  \
		पूर्ण                                 \
	पूर्ण जबतक (0)
#घोषणा packet_dump(msg, var, var_len)   \
	करो अणु                                   \
		अगर (packet_debug_logging) अणु          \
			prपूर्णांक_hex_dump(KERN_ALERT, msg, DUMP_PREFIX_NONE,  \
					16, 1, var, var_len, false); \
			अगर (debug_logging_sleep)           \
				msleep(debug_logging_sleep);     \
		पूर्ण                                    \
	पूर्ण जबतक (0)

व्योम __dump_sg(काष्ठा scatterlist *sg, अचिन्हित पूर्णांक skip, अचिन्हित पूर्णांक len);

#घोषणा dump_sg(sg, skip, len)     __dump_sg(sg, skip, len)

#अन्यथा /* !DEBUG_ON */

अटल अंतरभूत व्योम flow_log(स्थिर अक्षर *क्रमmat, ...)
अणु
पूर्ण

अटल अंतरभूत व्योम flow_dump(स्थिर अक्षर *msg, स्थिर व्योम *var, माप_प्रकार var_len)
अणु
पूर्ण

अटल अंतरभूत व्योम packet_log(स्थिर अक्षर *क्रमmat, ...)
अणु
पूर्ण

अटल अंतरभूत व्योम packet_dump(स्थिर अक्षर *msg, स्थिर व्योम *var, माप_प्रकार var_len)
अणु
पूर्ण

अटल अंतरभूत व्योम dump_sg(काष्ठा scatterlist *sg, अचिन्हित पूर्णांक skip,
			   अचिन्हित पूर्णांक len)
अणु
पूर्ण

#पूर्ण_अगर /* DEBUG_ON */

पूर्णांक spu_sg_at_offset(काष्ठा scatterlist *sg, अचिन्हित पूर्णांक skip,
		     काष्ठा scatterlist **sge, अचिन्हित पूर्णांक *sge_offset);

/* Copy sg data, from skip, length len, to dest */
व्योम sg_copy_part_to_buf(काष्ठा scatterlist *src, u8 *dest,
			 अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक skip);
/* Copy src पूर्णांकo scatterlist from offset, length len */
व्योम sg_copy_part_from_buf(काष्ठा scatterlist *dest, u8 *src,
			   अचिन्हित पूर्णांक len, अचिन्हित पूर्णांक skip);

पूर्णांक spu_sg_count(काष्ठा scatterlist *sg_list, अचिन्हित पूर्णांक skip, पूर्णांक nbytes);
u32 spu_msg_sg_add(काष्ठा scatterlist **to_sg,
		   काष्ठा scatterlist **from_sg, u32 *skip,
		   u8 from_nents, u32 tot_len);

व्योम add_to_ctr(u8 *ctr_pos, अचिन्हित पूर्णांक increment);

/* produce a message digest from data of length n bytes */
पूर्णांक करो_shash(अचिन्हित अक्षर *name, अचिन्हित अक्षर *result,
	     स्थिर u8 *data1, अचिन्हित पूर्णांक data1_len,
	     स्थिर u8 *data2, अचिन्हित पूर्णांक data2_len,
	     स्थिर u8 *key, अचिन्हित पूर्णांक key_len);

अक्षर *spu_alg_name(क्रमागत spu_cipher_alg alg, क्रमागत spu_cipher_mode mode);

व्योम spu_setup_debugfs(व्योम);
व्योम spu_मुक्त_debugfs(व्योम);
व्योम क्रमmat_value_ccm(अचिन्हित पूर्णांक val, u8 *buf, u8 len);

#पूर्ण_अगर
