<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _INTEL_PMT_CLASS_H
#घोषणा _INTEL_PMT_CLASS_H

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/xarray.h>
#समावेश <linux/types.h>
#समावेश <linux/bits.h>
#समावेश <linux/err.h>
#समावेश <linux/पन.स>

/* PMT access types */
#घोषणा ACCESS_BARID		2
#घोषणा ACCESS_LOCAL		3

/* PMT discovery base address/offset रेजिस्टर layout */
#घोषणा GET_BIR(v)		((v) & GENMASK(2, 0))
#घोषणा GET_ADDRESS(v)		((v) & GENMASK(31, 3))

काष्ठा पूर्णांकel_pmt_entry अणु
	काष्ठा bin_attribute	pmt_bin_attr;
	काष्ठा kobject		*kobj;
	व्योम __iomem		*disc_table;
	व्योम __iomem		*base;
	अचिन्हित दीर्घ		base_addr;
	माप_प्रकार			size;
	u32			guid;
	पूर्णांक			devid;
पूर्ण;

काष्ठा पूर्णांकel_pmt_header अणु
	u32	base_offset;
	u32	size;
	u32	guid;
	u8	access_type;
पूर्ण;

काष्ठा पूर्णांकel_pmt_namespace अणु
	स्थिर अक्षर *name;
	काष्ठा xarray *xa;
	स्थिर काष्ठा attribute_group *attr_grp;
	पूर्णांक (*pmt_header_decode)(काष्ठा पूर्णांकel_pmt_entry *entry,
				 काष्ठा पूर्णांकel_pmt_header *header,
				 काष्ठा device *dev);
पूर्ण;

bool पूर्णांकel_pmt_is_early_client_hw(काष्ठा device *dev);
पूर्णांक पूर्णांकel_pmt_dev_create(काष्ठा पूर्णांकel_pmt_entry *entry,
			 काष्ठा पूर्णांकel_pmt_namespace *ns,
			 काष्ठा platक्रमm_device *pdev, पूर्णांक idx);
व्योम पूर्णांकel_pmt_dev_destroy(काष्ठा पूर्णांकel_pmt_entry *entry,
			   काष्ठा पूर्णांकel_pmt_namespace *ns);
#पूर्ण_अगर
