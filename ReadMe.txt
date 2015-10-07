This is my modification of the chroma sdk.  I have changed the impl class to be far simpler to work with. See the console test application.  It is now trivial to light up or change colors on individual keys with a simplified interface:

CChromaSDKImpl c;
	c.Initialize();

	if (c.IsDeviceConnected(BLACKWIDOW_CHROMA))
	{
		cout << "it is" << endl;
	}


	//c.setKey("E", RGB(0, 0, 255));
	//c.setKey("H", RGB(0, 0, 255));

//simplified interface, just send a map
	std::map<std::string, DWORD> x = {
										{ "E", RGB(0, 0, 255) },	
										{ ";", RGB(255, 0, 255) }
									};

	c.setKeys(x);
	
	
	
	The existing implementation is, in my opinion, a mess.  Uses pieces of MFC (which no one uses any longer) and just some very strange and somewhat old programming practices and awkward interfaces.   So my change is a simplification to that. 
	
	Use at your own risk.
