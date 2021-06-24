<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43legacy_ILT_H_
#घोषणा B43legacy_ILT_H_

#घोषणा B43legacy_ILT_ROTOR_SIZE	53
बाह्य स्थिर u32 b43legacy_ilt_rotor[B43legacy_ILT_ROTOR_SIZE];
#घोषणा B43legacy_ILT_RETARD_SIZE	53
बाह्य स्थिर u32 b43legacy_ilt_retard[B43legacy_ILT_RETARD_SIZE];
#घोषणा B43legacy_ILT_FINEFREQA_SIZE	256
बाह्य स्थिर u16 b43legacy_ilt_finefreqa[B43legacy_ILT_FINEFREQA_SIZE];
#घोषणा B43legacy_ILT_FINEFREQG_SIZE	256
बाह्य स्थिर u16 b43legacy_ilt_finefreqg[B43legacy_ILT_FINEFREQG_SIZE];
#घोषणा B43legacy_ILT_NOISEA2_SIZE	8
बाह्य स्थिर u16 b43legacy_ilt_noisea2[B43legacy_ILT_NOISEA2_SIZE];
#घोषणा B43legacy_ILT_NOISEA3_SIZE	8
बाह्य स्थिर u16 b43legacy_ilt_noisea3[B43legacy_ILT_NOISEA3_SIZE];
#घोषणा B43legacy_ILT_NOISEG1_SIZE	8
बाह्य स्थिर u16 b43legacy_ilt_noiseg1[B43legacy_ILT_NOISEG1_SIZE];
#घोषणा B43legacy_ILT_NOISEG2_SIZE	8
बाह्य स्थिर u16 b43legacy_ilt_noiseg2[B43legacy_ILT_NOISEG2_SIZE];
#घोषणा B43legacy_ILT_NOISESCALEG_SIZE	27
बाह्य स्थिर u16 b43legacy_ilt_noisescaleg1[B43legacy_ILT_NOISESCALEG_SIZE];
बाह्य स्थिर u16 b43legacy_ilt_noisescaleg2[B43legacy_ILT_NOISESCALEG_SIZE];
बाह्य स्थिर u16 b43legacy_ilt_noisescaleg3[B43legacy_ILT_NOISESCALEG_SIZE];
#घोषणा B43legacy_ILT_SIGMASQR_SIZE	53
बाह्य स्थिर u16 b43legacy_ilt_sigmasqr1[B43legacy_ILT_SIGMASQR_SIZE];
बाह्य स्थिर u16 b43legacy_ilt_sigmasqr2[B43legacy_ILT_SIGMASQR_SIZE];


व्योम b43legacy_ilt_ग_लिखो(काष्ठा b43legacy_wldev *dev, u16 offset, u16 val);
व्योम b43legacy_ilt_ग_लिखो32(काष्ठा b43legacy_wldev *dev, u16 offset,
			   u32 val);
u16 b43legacy_ilt_पढ़ो(काष्ठा b43legacy_wldev *dev, u16 offset);

#पूर्ण_अगर /* B43legacy_ILT_H_ */
