<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Follows implementation found in linux/virtio_byteorder.h
 */
#अगर_अघोषित _LINUX_RPMSG_BYTEORDER_H
#घोषणा _LINUX_RPMSG_BYTEORDER_H
#समावेश <linux/types.h>
#समावेश <uapi/linux/rpmsg_types.h>

अटल अंतरभूत bool rpmsg_is_little_endian(व्योम)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u16 __rpmsg16_to_cpu(bool little_endian, __rpmsg16 val)
अणु
	अगर (little_endian)
		वापस le16_to_cpu((__क्रमce __le16)val);
	अन्यथा
		वापस be16_to_cpu((__क्रमce __be16)val);
पूर्ण

अटल अंतरभूत __rpmsg16 __cpu_to_rpmsg16(bool little_endian, u16 val)
अणु
	अगर (little_endian)
		वापस (__क्रमce __rpmsg16)cpu_to_le16(val);
	अन्यथा
		वापस (__क्रमce __rpmsg16)cpu_to_be16(val);
पूर्ण

अटल अंतरभूत u32 __rpmsg32_to_cpu(bool little_endian, __rpmsg32 val)
अणु
	अगर (little_endian)
		वापस le32_to_cpu((__क्रमce __le32)val);
	अन्यथा
		वापस be32_to_cpu((__क्रमce __be32)val);
पूर्ण

अटल अंतरभूत __rpmsg32 __cpu_to_rpmsg32(bool little_endian, u32 val)
अणु
	अगर (little_endian)
		वापस (__क्रमce __rpmsg32)cpu_to_le32(val);
	अन्यथा
		वापस (__क्रमce __rpmsg32)cpu_to_be32(val);
पूर्ण

अटल अंतरभूत u64 __rpmsg64_to_cpu(bool little_endian, __rpmsg64 val)
अणु
	अगर (little_endian)
		वापस le64_to_cpu((__क्रमce __le64)val);
	अन्यथा
		वापस be64_to_cpu((__क्रमce __be64)val);
पूर्ण

अटल अंतरभूत __rpmsg64 __cpu_to_rpmsg64(bool little_endian, u64 val)
अणु
	अगर (little_endian)
		वापस (__क्रमce __rpmsg64)cpu_to_le64(val);
	अन्यथा
		वापस (__क्रमce __rpmsg64)cpu_to_be64(val);
पूर्ण

#पूर्ण_अगर /* _LINUX_RPMSG_BYTEORDER_H */
