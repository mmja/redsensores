/**
 *
 * @author Joaquin Recas
 */

includes NetworkGenericComm;


configuration ProcEegEcg{
}
implementation {
  components Main,
             ProcEegEcgM,
             NetworkGenericComm,
             ReadEegEcgC;

  Main.StdControl     -> ReadEegEcgC.StdControl;
  Main.StdControl     -> NetworkGenericComm;
  
  ProcEegEcgM.ReadEegEcg   -> ReadEegEcgC;
	ProcEegEcgM.SendData     -> NetworkGenericComm.SendMsg[AM_DATA];
  

}
