<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_IF_HSR_H_
#घोषणा _LINUX_IF_HSR_H_

/* used to dअगरferentiate various protocols */
क्रमागत hsr_version अणु
	HSR_V0 = 0,
	HSR_V1,
	PRP_V1,
पूर्ण;

#अगर IS_ENABLED(CONFIG_HSR)
बाह्य bool is_hsr_master(काष्ठा net_device *dev);
बाह्य पूर्णांक hsr_get_version(काष्ठा net_device *dev, क्रमागत hsr_version *ver);
#अन्यथा
अटल अंतरभूत bool is_hsr_master(काष्ठा net_device *dev)
अणु
	वापस false;
पूर्ण
अटल अंतरभूत पूर्णांक hsr_get_version(काष्ठा net_device *dev,
				  क्रमागत hsr_version *ver)
अणु
	वापस -EINVAL;
पूर्ण
#पूर्ण_अगर /* CONFIG_HSR */

#पूर्ण_अगर /*_LINUX_IF_HSR_H_*/
