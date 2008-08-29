/**
 *
 * @author Joaquín Recas
 */


configuration ReadEegEcgC{
  provides interface StdControl;
  provides interface ReadEegEcg;
}
implementation {
  components ReadEegEcgM,
             MSP430InterruptC;

  StdControl=ReadEegEcgM;
  ReadEegEcg=ReadEegEcgM;

  //Enable signal sync.
  ReadEegEcgM.Enable        -> MSP430InterruptC.Port20;
}
