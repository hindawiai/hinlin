<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित B43_DEBUGFS_H_
#घोषणा B43_DEBUGFS_H_

काष्ठा b43_wldev;
काष्ठा b43_txstatus;

क्रमागत b43_dyndbg अणु		/* Dynamic debugging features */
	B43_DBG_XMITPOWER,
	B43_DBG_DMAOVERFLOW,
	B43_DBG_DMAVERBOSE,
	B43_DBG_PWORK_FAST,
	B43_DBG_PWORK_STOP,
	B43_DBG_LO,
	B43_DBG_FIRMWARE,
	B43_DBG_KEYS,
	B43_DBG_VERBOSESTATS,
	__B43_NR_DYNDBG,
पूर्ण;

#अगर_घोषित CONFIG_B43_DEBUG

काष्ठा dentry;

#घोषणा B43_NR_LOGGED_TXSTATUS	100

काष्ठा b43_txstatus_log अणु
	/* This काष्ठाure is रक्षित by wl->mutex */

	काष्ठा b43_txstatus *log;
	पूर्णांक end;
पूर्ण;

काष्ठा b43_dfs_file अणु
	काष्ठा dentry *dentry;
	अक्षर *buffer;
	माप_प्रकार data_len;
पूर्ण;

काष्ठा b43_dfsentry अणु
	काष्ठा b43_wldev *dev;
	काष्ठा dentry *subdir;

	काष्ठा b43_dfs_file file_shm16पढ़ो;
	काष्ठा b43_dfs_file file_shm16ग_लिखो;
	काष्ठा b43_dfs_file file_shm32पढ़ो;
	काष्ठा b43_dfs_file file_shm32ग_लिखो;
	काष्ठा b43_dfs_file file_mmio16पढ़ो;
	काष्ठा b43_dfs_file file_mmio16ग_लिखो;
	काष्ठा b43_dfs_file file_mmio32पढ़ो;
	काष्ठा b43_dfs_file file_mmio32ग_लिखो;
	काष्ठा b43_dfs_file file_txstat;
	काष्ठा b43_dfs_file file_txघातer_g;
	काष्ठा b43_dfs_file file_restart;
	काष्ठा b43_dfs_file file_loctls;

	काष्ठा b43_txstatus_log txstatlog;

	/* The cached address क्रम the next mmio16पढ़ो file पढ़ो */
	u16 mmio16पढ़ो_next;
	/* The cached address क्रम the next mmio32पढ़ो file पढ़ो */
	u16 mmio32पढ़ो_next;

	/* The cached address क्रम the next shm16पढ़ो file पढ़ो */
	u32 shm16पढ़ो_routing_next;
	u32 shm16पढ़ो_addr_next;
	/* The cached address क्रम the next shm32पढ़ो file पढ़ो */
	u32 shm32पढ़ो_routing_next;
	u32 shm32पढ़ो_addr_next;

	/* Enabled/Disabled list क्रम the dynamic debugging features. */
	bool dyn_debug[__B43_NR_DYNDBG];
	/* Dentries क्रम the dynamic debugging entries. */
	काष्ठा dentry *dyn_debug_dentries[__B43_NR_DYNDBG];
पूर्ण;

bool b43_debug(काष्ठा b43_wldev *dev, क्रमागत b43_dyndbg feature);

व्योम b43_debugfs_init(व्योम);
व्योम b43_debugfs_निकास(व्योम);
व्योम b43_debugfs_add_device(काष्ठा b43_wldev *dev);
व्योम b43_debugfs_हटाओ_device(काष्ठा b43_wldev *dev);
व्योम b43_debugfs_log_txstat(काष्ठा b43_wldev *dev,
			    स्थिर काष्ठा b43_txstatus *status);

#अन्यथा /* CONFIG_B43_DEBUG */

अटल अंतरभूत bool b43_debug(काष्ठा b43_wldev *dev, क्रमागत b43_dyndbg feature)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम b43_debugfs_init(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम b43_debugfs_निकास(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम b43_debugfs_add_device(काष्ठा b43_wldev *dev)
अणु
पूर्ण
अटल अंतरभूत व्योम b43_debugfs_हटाओ_device(काष्ठा b43_wldev *dev)
अणु
पूर्ण
अटल अंतरभूत व्योम b43_debugfs_log_txstat(काष्ठा b43_wldev *dev,
					  स्थिर काष्ठा b43_txstatus *status)
अणु
पूर्ण

#पूर्ण_अगर /* CONFIG_B43_DEBUG */

#पूर्ण_अगर /* B43_DEBUGFS_H_ */
