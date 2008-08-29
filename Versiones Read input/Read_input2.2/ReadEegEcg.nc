
//@author Joaquin Recas

interface ReadEegEcg{
  /**
   * Signalled when an interrupt occurs on a port
   */
  async event void fired(uint16_t *pData);
}

