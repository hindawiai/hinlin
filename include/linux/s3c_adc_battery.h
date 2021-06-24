<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _S3C_ADC_BATTERY_H
#घोषणा _S3C_ADC_BATTERY_H

काष्ठा s3c_adc_bat_thresh अणु
	पूर्णांक volt; /* mV */
	पूर्णांक cur; /* mA */
	पूर्णांक level; /* percent */
पूर्ण;

काष्ठा s3c_adc_bat_pdata अणु
	पूर्णांक (*init)(व्योम);
	व्योम (*निकास)(व्योम);
	व्योम (*enable_अक्षरger)(व्योम);
	व्योम (*disable_अक्षरger)(व्योम);

	स्थिर काष्ठा s3c_adc_bat_thresh *lut_noac;
	अचिन्हित पूर्णांक lut_noac_cnt;
	स्थिर काष्ठा s3c_adc_bat_thresh *lut_acin;
	अचिन्हित पूर्णांक lut_acin_cnt;

	स्थिर अचिन्हित पूर्णांक volt_channel;
	स्थिर अचिन्हित पूर्णांक current_channel;
	स्थिर अचिन्हित पूर्णांक backup_volt_channel;

	स्थिर अचिन्हित पूर्णांक volt_samples;
	स्थिर अचिन्हित पूर्णांक current_samples;
	स्थिर अचिन्हित पूर्णांक backup_volt_samples;

	स्थिर अचिन्हित पूर्णांक volt_mult;
	स्थिर अचिन्हित पूर्णांक current_mult;
	स्थिर अचिन्हित पूर्णांक backup_volt_mult;
	स्थिर अचिन्हित पूर्णांक पूर्णांकernal_impedance;

	स्थिर अचिन्हित पूर्णांक backup_volt_max;
	स्थिर अचिन्हित पूर्णांक backup_volt_min;
पूर्ण;

#पूर्ण_अगर
