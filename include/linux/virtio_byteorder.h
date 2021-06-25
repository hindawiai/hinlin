<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_VIRTIO_BYTEORDER_H
#घोषणा _LINUX_VIRTIO_BYTEORDER_H
#समावेश <linux/types.h>
#समावेश <uapi/linux/virtio_types.h>

अटल अंतरभूत bool virtio_legacy_is_little_endian(व्योम)
अणु
#अगर_घोषित __LITTLE_ENDIAN
	वापस true;
#अन्यथा
	वापस false;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u16 __virtio16_to_cpu(bool little_endian, __virtio16 val)
अणु
	अगर (little_endian)
		वापस le16_to_cpu((__क्रमce __le16)val);
	अन्यथा
		वापस be16_to_cpu((__क्रमce __be16)val);
पूर्ण

अटल अंतरभूत __virtio16 __cpu_to_virtio16(bool little_endian, u16 val)
अणु
	अगर (little_endian)
		वापस (__क्रमce __virtio16)cpu_to_le16(val);
	अन्यथा
		वापस (__क्रमce __virtio16)cpu_to_be16(val);
पूर्ण

अटल अंतरभूत u32 __virtio32_to_cpu(bool little_endian, __virtio32 val)
अणु
	अगर (little_endian)
		वापस le32_to_cpu((__क्रमce __le32)val);
	अन्यथा
		वापस be32_to_cpu((__क्रमce __be32)val);
पूर्ण

अटल अंतरभूत __virtio32 __cpu_to_virtio32(bool little_endian, u32 val)
अणु
	अगर (little_endian)
		वापस (__क्रमce __virtio32)cpu_to_le32(val);
	अन्यथा
		वापस (__क्रमce __virtio32)cpu_to_be32(val);
पूर्ण

अटल अंतरभूत u64 __virtio64_to_cpu(bool little_endian, __virtio64 val)
अणु
	अगर (little_endian)
		वापस le64_to_cpu((__क्रमce __le64)val);
	अन्यथा
		वापस be64_to_cpu((__क्रमce __be64)val);
पूर्ण

अटल अंतरभूत __virtio64 __cpu_to_virtio64(bool little_endian, u64 val)
अणु
	अगर (little_endian)
		वापस (__क्रमce __virtio64)cpu_to_le64(val);
	अन्यथा
		वापस (__क्रमce __virtio64)cpu_to_be64(val);
पूर्ण

#पूर्ण_अगर /* _LINUX_VIRTIO_BYTEORDER */
