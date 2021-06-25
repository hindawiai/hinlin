<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Raytheon wireless LAN PCMCIA card driver क्रम Linux 
   A  PCMCIA client driver क्रम the Raylink wireless network card
   Written by Corey Thomas
*/

#अगर_अघोषित _RAY_CS_H_
#घोषणा _RAY_CS_H_

काष्ठा beacon_rx अणु
    काष्ठा mac_header mac;
    UCHAR बारtamp[8];
    UCHAR beacon_पूर्णांकvl[2];
    UCHAR capability[2];
    UCHAR elements[माप(काष्ठा essid_element) 
                  + माप(काष्ठा rates_element)
                  + माप(काष्ठा freq_hop_element) 
                  + माप(काष्ठा japan_call_sign_element)
                  + माप(काष्ठा tim_element)];
पूर्ण;

/* Return values क्रम get_मुक्तअणु,_txपूर्ण_ccs */
#घोषणा ECCSFULL  (-1)
#घोषणा ECCSBUSY  (-2)
#घोषणा ECARDGONE (-3)

प्रकार काष्ठा ray_dev_t अणु
    पूर्णांक card_status;
    पूर्णांक authentication_state;
    व्योम __iomem *sram;            /* poपूर्णांकer to beginning of shared RAM     */
    व्योम __iomem *amem;            /* poपूर्णांकer to attribute mem winकरोw        */
    व्योम __iomem *rmem;            /* poपूर्णांकer to receive buffer winकरोw       */
    काष्ठा pcmcia_device *finder;            /* poपूर्णांकer back to काष्ठा pcmcia_device क्रम card    */
    काष्ठा समयr_list समयr;
    अचिन्हित दीर्घ tx_ccs_lock;
    अचिन्हित दीर्घ ccs_lock;
    पूर्णांक   dl_param_ccs;
    जोड़ अणु
        काष्ठा b4_startup_params b4;
        काष्ठा b5_startup_params b5;
    पूर्ण sparm;
    पूर्णांक समयout_flag;
    UCHAR supported_rates[8];
    UCHAR japan_call_sign[12];
    काष्ठा startup_res_6 startup_res;
    पूर्णांक num_multi;
    /* Network parameters from start/join */
    UCHAR bss_id[6];
    UCHAR auth_id[6];
    UCHAR net_शेष_tx_rate;
    UCHAR encryption;
    काष्ठा net_device_stats stats;

    UCHAR net_type;
    UCHAR sta_type;
    UCHAR fw_ver;
    UCHAR fw_bld;
    UCHAR fw_var;
    UCHAR ASIC_version;
    UCHAR assoc_id[2];
    UCHAR tib_length;
    UCHAR last_rsl;
    पूर्णांक beacon_rxed;
    काष्ठा beacon_rx last_bcn;
    iw_stats	wstats;		/* Wireless specअगरic stats */
#अगर_घोषित WIRELESS_SPY
    काष्ठा iw_spy_data		spy_data;
    काष्ठा iw_खुला_data	wireless_data;
#पूर्ण_अगर	/* WIRELESS_SPY */

पूर्ण ray_dev_t;
/*****************************************************************************/

#पूर्ण_अगर /* _RAY_CS_H_ */
