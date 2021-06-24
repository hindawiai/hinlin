<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UDF_ENDIAN_H
#घोषणा __UDF_ENDIAN_H

#समावेश <यंत्र/byteorder.h>
#समावेश <linux/माला.स>

अटल अंतरभूत काष्ठा kernel_lb_addr lelb_to_cpu(काष्ठा lb_addr in)
अणु
	काष्ठा kernel_lb_addr out;

	out.logicalBlockNum = le32_to_cpu(in.logicalBlockNum);
	out.partitionReferenceNum = le16_to_cpu(in.partitionReferenceNum);

	वापस out;
पूर्ण

अटल अंतरभूत काष्ठा lb_addr cpu_to_lelb(काष्ठा kernel_lb_addr in)
अणु
	काष्ठा lb_addr out;

	out.logicalBlockNum = cpu_to_le32(in.logicalBlockNum);
	out.partitionReferenceNum = cpu_to_le16(in.partitionReferenceNum);

	वापस out;
पूर्ण

अटल अंतरभूत काष्ठा लघु_ad lesa_to_cpu(काष्ठा लघु_ad in)
अणु
	काष्ठा लघु_ad out;

	out.extLength = le32_to_cpu(in.extLength);
	out.extPosition = le32_to_cpu(in.extPosition);

	वापस out;
पूर्ण

अटल अंतरभूत काष्ठा लघु_ad cpu_to_lesa(काष्ठा लघु_ad in)
अणु
	काष्ठा लघु_ad out;

	out.extLength = cpu_to_le32(in.extLength);
	out.extPosition = cpu_to_le32(in.extPosition);

	वापस out;
पूर्ण

अटल अंतरभूत काष्ठा kernel_दीर्घ_ad lela_to_cpu(काष्ठा दीर्घ_ad in)
अणु
	काष्ठा kernel_दीर्घ_ad out;

	out.extLength = le32_to_cpu(in.extLength);
	out.extLocation = lelb_to_cpu(in.extLocation);

	वापस out;
पूर्ण

अटल अंतरभूत काष्ठा दीर्घ_ad cpu_to_lela(काष्ठा kernel_दीर्घ_ad in)
अणु
	काष्ठा दीर्घ_ad out;

	out.extLength = cpu_to_le32(in.extLength);
	out.extLocation = cpu_to_lelb(in.extLocation);

	वापस out;
पूर्ण

अटल अंतरभूत काष्ठा kernel_extent_ad leea_to_cpu(काष्ठा extent_ad in)
अणु
	काष्ठा kernel_extent_ad out;

	out.extLength = le32_to_cpu(in.extLength);
	out.extLocation = le32_to_cpu(in.extLocation);

	वापस out;
पूर्ण

#पूर्ण_अगर /* __UDF_ENDIAN_H */
